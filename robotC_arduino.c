#pragma config(Sensor, S1,     HTSPB,          sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers\hitechnic-superpro.h"
/*
												sendArduinoCommand():
Supporting method for getMPUHeading() and getMPUAccel()
Command numbers correlate with different functions compiled to the Arduino

Command 1: Tell the arduino to blink LED (debug)

Command 2: Receive the first half of heading from the arduino
Command 3: Receive the second half of heading from the arduino
NOTE: To receive the full heading, call getMPUHeading(), which
bitwise or pairs the values to return actual heading.


Command 4: receive raw acceleration on the x axis
(Command 5: receive the second half of raw acceleration from the arduino)
NOTE: To receive full acceleration, call getMPUAccel(), which bitwise
or pairs the two values to return the actual heading.

Command 6: Receive raw values from the arduino
Command 7: Receive second half of raw x values from arduino
*/

signed int sendArduinoCommand(unsigned char command)
{
	signed int result;
	HTSPBsetupIO(HTSPB, 0xFF); //sets B0-7 to output
	HTSPBwriteStrobe(HTSPB, command); // send the command via S0-3
	if (command >= 2)
	{
		HTSPBsetupIO(HTSPB, 0x00); // sets BO-7 to input so that it can receive
		result = HTSPBreadIO(HTSPB, 0xFF);
	}
	return result;
}

//Get the current heading from the MPU6050 gyro
short getMPUHeading()
{
	hogCPU();
	unsigned char add1 = sendArduinoCommand(2);
	signed char add2 = sendArduinoCommand(3);
	short MPUheading = add1 | (add2 << 8);
	if(MPUheading < 0)
	{
		MPUheading += 360;
	}
	//wait1Msec(50);
	releaseCPU();
	displayCenteredBigTextLine(2, "%d", MPUheading);
	return MPUheading;
}

short getTest()
{
	hogCPU();
	short testNum = sendArduinoCommand(4);
	return testNum;
	releaseCPU();
}

task main()
{
	/*int test = 0;
	while(true)
	{
		test = getTest();
		displayCenteredBigTextLine(0, "test:%d", test);
	}*/

	/*int test = 0;
	while(true)
	{
		test = getMPUHeading();
		displayCenteredBigTextLine(0, "test:%d", test);
		wait10Msec(1);
	}*/

	int heading = 0;
	int MPUheading = 0;
	int diff;
	int oldHeading;

  wait10Msec(100);
  int init = getMPUHeading();
  oldHeading = init;
  //displayCenteredBigTextLine(0, "init:%d", init);
  wait10Msec(100);
  //displayCenteredBigTextLine(2, "init:%d", heading);

	while(heading < 90){
			MPUheading = getMPUHeading();
			diff = abs(MPUheading - oldHeading);
			if ((diff < 60)||(360 - diff < 60)){
				heading = MPUheading - init;
	    	if(MPUheading < init)//accomodate for rollover
	    	{
	    		heading = (MPUheading + 360) - init;
	    	}
	    	oldHeading = MPUheading;
				//displayCenteredBigTextLine(2, "%d", heading);
	    	//displayCenteredBigTextLine(4, "%d", MPUheading);
	 		}
	 	 	wait1Msec(5);
	}
	while(true){}
}
