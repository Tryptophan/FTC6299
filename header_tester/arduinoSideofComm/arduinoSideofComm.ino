#include <Wire.h>

#define DATA_PIN_0 8 //Ports 8 - 13 as well as A0/1 are data pins
#define DATA_WIDTH 8
#define CMD_PIN_0 4 //Ports 4 - 7 are command pins
#define CMD_WIDTH 4 //Width of command pins
#define WR_INT 3 //The "WR" port on SP for sending pulse is port 3 on Arduino

int command, data, request, heading, GyZ;
const int MPU = 0x68;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); //PWR_MGMT register
  Wire.write(0); //Wakes up the gyro
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void hiSP()
{
  command = 0;
  data = 0;
  
  //If the command is perform something from SP
  for (int i = 0; i < CMD_WIDTH; i++)
  {
    command += digitalRead(CMD_PIN_0 + i) << i;
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
  for (int i = 0; i < DATA_WIDTH; i++)
  {
    pinMode(DATA_PIN_0 + i, INPUT);
  }
}

void loop()
{
  attachInterrupt(WR_INT, hiSP, RISING);
  Wire.beginTransmission(MPU);
  Wire.write(0x47);
  Wire.requestFrom(MPU,2, true);
  GyZ=Wire.read() <<8 | Wire.read();
}

