int command, data, request;

void setup()
{
}

void hiSP()
{
  command = 0;
  data = 0;
  if(command <= 2)
  {
     for (int i = 0; i < 4; i++)
    {
      command += digitalRead(4+i) << i;
    }
    for (int i - 0; i < 8; i++)
    {
      data += digitalRead(DATA_PIN_0 + i) << i;
    }
    request = 1;
  }
  
  if (command >
}
void loop()
{
  if(attachInterrupt(3, hiSP, RISING))
  {}
}

