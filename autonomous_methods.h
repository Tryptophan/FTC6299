#include "libs.h";

string smuxPower = "Bad";

void initializeRobot() {

}

// Finds the ir beacon, dumps the block, and parks on the ramp
void autonomous(int suspend, int park) {
	wait10Msec(suspend * 100);
	moveTo(40, 500, 0.8);
	turn(25, 90);
}

void autoFrontDump(int suspend) {
	turn(25,180);
	moveTo(40, 500, 0.8);
}
