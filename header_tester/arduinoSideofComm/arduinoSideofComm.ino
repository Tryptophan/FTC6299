#define DATA_PIN_0 8 //Ports 8 - 13 as well as A0/1 are data pins
#define DATA_WIDTH 8
#define CMD_PIN_0 4 //Ports 4 - 7 are command pins
#define WR_INT 3 //The "WR" port on SP for sending pulse is port 3 on Arduino

int command, data, request, heading, zRaw;

void setup()
{
}

void hiSP()
{
  command = 0;
  data = 0;
  
  //If the command is perform something from SP
  if (command <= 2)
  {
     for (int i = 0; i < 4; i++)
    {
      command += digitalRead(CMD_PIN_0 + i) << i;
    }
  }
  
  //If the commands are to send data back to the SP
  if (command > 2)
  {
    switch (command)
    {
      case 3:
        data = heading;
        break;
      case 4:
        data = zRaw; 
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
        digitalWrite(DATA_PIN_0 + i, LOW);
    }
    
    for (int i = 0; i < DATA_WIDTH; i++)
    {
      pinMode(DATA_PIN_0 + i, INPUT);
    }
  }
}

void loop()
{
  attachInterrupt(WR_INT, hiSP, RISING);
}

