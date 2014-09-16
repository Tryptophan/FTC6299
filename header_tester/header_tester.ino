#include"Wire.h"

const int MPU=0x68;  // I2C address of the MPU-6050 

int heading = 0; 
int GyX; 

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(38400);
}

//default at power up: 250 degress/second
//MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
void loop()
{
  //GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  Serial.println(getHeading());
}

int getHeading()
{
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  heading += GyX * (float) (20/1000);
  delay(20);
  return heading;
}

