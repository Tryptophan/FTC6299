#include "drivers\JoystickDriver.c";
#include "autonomous_methods.h";
#include "libs.h"

/*
	Made by Team 6299 QuadX
		- Jacob Greenway
		- Joshua Johnson
		- Linnea May
*/

int i, j, begin, suspend = 0;
int tube = 2;
string sides[2] = {"Ramp", "Zone"};
string side = sides[0];

string programs[3] = {"Autonomous", "autoBDump", "test"};
string file = programs[0];

int toggle = 0;

void startupCheck(){
	if (HTGYROreadRot(SENSOR_GYRO) == 403){
		playSound(soundException);
		displayTextLine(6, " Check Gyro");
	}
	if (externalBattery < 13600){
		playSound(soundBlip);
		displayTextLine(7, " Battery Low");
	}
}

void toggleMenu() {
	toggle++;
	if (toggle > 3) {
		toggle = 0;
		wait1Msec(250);
		return;
	}
	wait1Msec(250);
}

void toggleSubMenu(int dir) {
	switch(toggle) {
		case 0 :
			// Select Right
			if (dir == 1 && i < 2) {
				i++;
				file = programs[i];
				wait1Msec(250);
			}

			// Select Left
			else if (dir == 2 && i > 0) {
				i--;
				file = programs[i];
				wait1Msec(250);
			}
			break;

		case 1 :
			// Select Right
			if (dir == 1) {
				suspend++;
				wait1Msec(250);
			}

			// Select Left
			else if (dir == 2 && suspend > 0) {
				suspend--;
				wait1Msec(250);
			}
			break;

		case 2 :
			// Select Right
			if (dir == 1 && tube < 3) {
				tube++;
				wait1Msec(250);
			}

			// Select Left
			else if (dir == 2 && tube > 1) {
				tube--;
				wait1Msec(250);
			}
			break;

		case 3 :
			// Select Right
			if (dir == 1 && j < 2) {
				j++;
				side = sides[j];
				begin++;
				wait1Msec(250);
			}

			// Select Left
			else if (dir == 2 && j > 0) {
				j--;
				side = sides[j];
				begin--;
				wait1Msec(250);
			}
			break;
	}
}

task chooser() {
	initializeRobot();
	while (true) {
		startupCheck();
		if (nNxtButtonPressed == 3) {
			toggleMenu();
			wait1Msec(250);
		}
		else if (nNxtButtonPressed == 2 || nNxtButtonPressed == 1) {
			toggleSubMenu(nNxtButtonPressed);
			wait1Msec(250);
		}

		if (toggle == 0) {
			displayTextLine(0, "*Pgm: %s", file);
			displayTextLine(1, " Delay: %2i", suspend);
			displayTextLine(2, " Tube: %2i", tube);
			displayTextLine(3, " Side: %s", side);

			displayTextLine(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			displayTextLine(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}
		else if (toggle == 1) {
			displayTextLine(0, " Pgm: %s", file);
			displayTextLine(1, "*Delay: %2i", suspend);
			displayTextLine(2, " Tube: %2i", tube);
			displayTextLine(3, " Side: %s", side);

			displayTextLine(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			displayTextLine(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}

		else if (toggle == 2) {
			displayTextLine(0, " Pgm: %s", file);
			displayTextLine(1, " Delay: %2i", suspend);
			displayTextLine(2, "*Tube: %2i", tube);
			displayTextLine(3, " Side: %s", side);

			displayTextLine(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			displayTextLine(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}

		else if (toggle == 3) {
			displayTextLine(0, " Pgm: %s", file);
			displayTextLine(1, " Delay: %2i", suspend);
			displayTextLine(2, " Tube: %2i", tube);
			displayTextLine(3, "*Side: %s", side);

			displayTextLine(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			displayTextLine(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}
		wait1Msec(5);
		eraseDisplay();
	}
}
