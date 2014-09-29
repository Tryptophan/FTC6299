#include "drivers\JoystickDriver.c";

int i, j, suspend = 0;
string sides[3] = {"Auto", "Right", "Left"};
string side = sides[0];

string programs[3] = {"Autonomous", "autoBDump", "autoFDump"};
string file = programs[0];

int toggle = 0;

void toggleMenu() {
	toggle++;
	if (toggle > 2) {
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
			if (dir == 1 && j < 2) {
				j++;
				side = sides[j];
				wait1Msec(250);
			}

			// Select Left
			else if (dir == 2 && j > 0) {
				j--;
				side = sides[j];
				wait1Msec(250);
			}
			break;
	}
}

task chooser() {
	while (true) {
		if (nNxtButtonPressed == 3) {
			toggleMenu();
			wait1Msec(250);
		}
		else if (nNxtButtonPressed == 2 || nNxtButtonPressed == 1) {
			toggleSubMenu(nNxtButtonPressed);
			wait1Msec(250);
		}

		if (toggle == 0) {
			nxtDisplayString(0, "*Pgm: %s", file);
			nxtDisplayString(1, " Delay: %2i", suspend);
			nxtDisplayString(2, " Side: %s", side);

			nxtDisplayString(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			nxtDisplayString(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}
		else if (toggle == 1) {
			nxtDisplayString(0, " Pgm: %s", file);
			nxtDisplayString(1, "*Delay: %2i", suspend);
			nxtDisplayString(2, " Side: %s", side);

			nxtDisplayString(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			nxtDisplayString(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}

		else if (toggle == 2) {
			nxtDisplayString(0, " Pgm: %s", file);
			nxtDisplayString(1, " Delay: %2i", suspend);
			nxtDisplayString(2, "*Side: %s", side);

			nxtDisplayString(4, " NXT Batt: %3f", (float)nAvgBatteryLevel / 1000);
			nxtDisplayString(5, " EXT Batt: %3f", (float)externalBattery / 1000);
		}
		wait1Msec(5);
		eraseDisplay();
	}
}
