#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h"

//Check to see if interrupt ports match the DMP6
#define DATA_PIN_0 8 //Ports 8 - 13 as well as A0/1 are data pins
#define DATA_WIDTH 8
#define CMD_PIN_0 4 //Ports 4 - 7 are command pins
#define CMD_WIDTH 4 //Width of command pins
#define WR_INT 1 //The "WR" port on SP for sending pulse is port 3 on Arduino

volatile int command, request, heading, GyZ, accel; //volatile b/c used in interrupt and main loop; //getting closer, but not there yet
//volatile signed short accel;
volatile byte data;
const int MPU = 0x68;
int led = 13;
MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

//Gryo Interrupt detection
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

void setup()
{
  pinMode(led, OUTPUT);
  Wire.begin();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); //PWR_MGMT register
  Wire.write(0); //Wakes up the gyro
  Wire.endTransmission(true);
  Serial.begin(9600);
  attachInterrupt(WR_INT, hiSP, RISING);
  
  //Setting up gyro
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  //Fastwire::setup(400, true);
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  devStatus = mpu.dmpInitialize();
  mpu.setZGyroOffset(0);
  mpu.setZAccelOffset(1688);
  
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      attachInterrupt(0, dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
  } 
}

void hiSP()
{ 
  //reads and sets command to the number sent
  for (int i = 0; i < CMD_WIDTH; i++)
  {
    command += digitalRead(CMD_PIN_0 + i) << i;
  }
  request = 1; //to alert the main method that new command has been sent

  //if command is 2 or greater, send back a specified value
  if (command >= 2)
  {
    //heading = -300;
    switch(command)
    {
      case 2:
        data = heading;
        break;
      case 3: 
        data = heading >> 8; 
        break;
      default: 
        data = 6; 
        break;
    }
     
  for (int i = 0; i < DATA_WIDTH; i++)
    {
      pinMode(DATA_PIN_0 + i, OUTPUT);
      if (data & (1 << i))
      {
        digitalWrite(DATA_PIN_0 + i, HIGH);
      }
      else
      {
        digitalWrite(DATA_PIN_0 + i, LOW);
      }
    }
  }
  else
  {
    //reset the pins to input after sending the data- allows to receive new comamnds
    for (int i = 0; i < DATA_WIDTH; i++)
    {
      pinMode(DATA_PIN_0 + i, INPUT);
    }
  }
}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);
  
  GyZ = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //GyZ = mpu.getRotationZ();
  Serial.print("raw: ");
  Serial.println(GyZ);

  //If command = 1; good to use for debug
  if (request == 1 && command == 1)
  {
    mpu.setZGyroOffset(GyZ * -1);
    delay(100);
    
    /*while(true)
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
    }*/
  }
  
  //request = 0;
  
  if(!dmpDataReady) return;
  command = 0;
  data = 0;
  
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount(); // get current FIFO count
  
// check for overflow (this should never happen)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
  {
    mpu.resetFIFO(); // reset so we can continue cleanly
    Serial.print("FIFO Overflow!");
  }
 
  else if (mpuIntStatus & 0x02) 
  {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount(); // wait for correct available data length, should be SHORT
    mpu.getFIFOBytes(fifoBuffer, packetSize); // read a packet from FIFO
    
    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    
/********** READ THE GYRO HEADING **********/
      
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetEuler(euler, &q);
      heading = euler[0] * 180/M_PI;
      
      Serial.println(heading);
      Serial.print("\t");
     
/********** READ ACCELEROMETER X AXIS **********/
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    accel = aaReal.x;
    
    if (abs(accel) < 100)
    {
        accel = 0;
    }
    
    accel /= 78.4; //78.4
    /*Serial.print("x axis: ");
    Serial.println(accel);*/
  }
}
