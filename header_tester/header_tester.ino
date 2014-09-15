#include<Wire.h>
#include<Timer-master/Timer.h>

const int MPU=0x68;  // I2C address of the MPU-6050

int heading = 0; 
Timer t = 0; 

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

}

//default at power up: 250 degress/second
//MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
void loop()
{
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  t.run(); 
}

void getHeading(int time)
{
  t.restartTimer(); 
  while(t < time)
  {
    heading += GyX * (float) (250/1000); 
  }
}

