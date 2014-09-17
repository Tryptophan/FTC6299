#include"Wire.h"

const int MPU=0x68;  // I2C address of the MPU-6050 
#define MPU6050_GYRO_ZOUT_H        0x47   // R
int heading = 0; 
int GyZ; 

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x47);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true);  // request a total of 14 registers
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.println(" | GyZ = "); Serial.println(GyZ);
  Serial.println(getHeading());
  delay(300);
}

int getHeading()
{
  heading += GyZ * (float) (20/1000);
  return heading;
  delay(20);
}

