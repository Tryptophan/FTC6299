#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)

#include "hitechnic-superpro.h"
/*
Command numbers correlate with different functions compiled to the Arduino
command 1: tell the arduino to calculate heading (input)
command 2: tell the arduino to get raw value of z axis (input)
command 3: receive the heading from the arduino (output)

*/

int result;

//sends a command to the Arduino over S0-3, and gets data from B0-7
unsigned char sendArduinoCommand(unsigned char command)
{
	if(command < 2)
	{
		HTSPBsetupIO(HTSPB, 0xFF); //sets B0-7 to output ????
		HTSPBwriteStrobe(HTSPB, command); // send the command via S0-3
	}
	else
	{
		HTSPBsetupIO(HTSPB, 0x00); // sets BO-7 to input
		result = HTSPBreadIO(HTSPB, 0xFF);
	}
	return result;
}

task main()
{
	sendArduinoCommand(1);
	//uninstall, delete anything left over in Program files,
	//and reinstall. ughhh.

}
