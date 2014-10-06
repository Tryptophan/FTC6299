#include <Wire.h>

#define DATA_PIN_0 8 //Ports 8 - 13 as well as A0/1 are data pins
#define DATA_WIDTH 8
#define CMD_PIN_0 4 //Ports 4 - 7 are command pins
#define CMD_WIDTH 4 //Width of command pins
#define WR_INT 1 //The "WR" port on SP for sending pulse is port 3 on Arduino

volatile int command, data, request, heading, GyZ; //volatile b/c used in interrupt and main loop
const int MPU = 0x68;
int led = 13;

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
}

void hiSP()
{
  command = 0;
  data = 0;
  request = 0;
  
  //reads and sets command to the number sent
  for (int i = 0; i < CMD_WIDTH; i++)
  {
    command += digitalRead(CMD_PIN_0 + i) << i;
  }
  request = 1; //to alert the main method that new command has been sent

  //if command is 2 or greater, send back a certain value
  if (command >= 2)
  {
    switch(command)
    {
      case 2:
        data = heading;
        break;
      case 3:
        data = 3;
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
    
    //reset the pins to input after sending the data- allows to receive new comamnds
    for (int i = 0; i < DATA_WIDTH; i++)
    {
      pinMode(DATA_PIN_0 + i, INPUT);
    }
  }
}

void loop()
{
  if (request == 1)
  {
    digitalWrite(led, LOW);
    delay(1000);
    digitalWrite(led, HIGH);
    delay(1000);
  }
  if (command == 3)
  {
    Serial.print("Got command");
  }
  request = 0;
}

