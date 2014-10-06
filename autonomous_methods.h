#include "libs.h";

string smuxPower = "Bad";

void initializeRobot() {
	nVolume = 4;
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void autonomous(int suspend, int park) {
	wait10Msec(suspend * 100);
	/*moveTo(40, 500, 0.8);
	turn(25, 90); */
	playSound(soundBeepBeep);
}

void autoFrontDump(int suspend) {
	wait10Msec(suspend * 100);

}

void test(int suspend){
	wait10Msec(suspend * 100);

}
