#include "libs.h";

void initializeRobot() {
	nVolume = 4;
	latch(false);
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void bare(int suspend, int begin) {
	wait10Msec(suspend * 100);
	if (begin == 1){  //Parking Zone
	}
	if (begin == 0){  //Ramp
		playSound(soundBeepBeep);
		moveTo(-40, -3500, 0.8);
		latch(true);
		turn(30, 45);
		moveTo(30, 250, 0.8);
		turn(30, 90);
		turn(30, 90);
		moveTo(-30, -3500, 0.8);
		latch(false);
	}

}

void autoFrontDump(int suspend) {
	wait10Msec(suspend * 100);

}

void test(int suspend){
	wait10Msec(suspend * 100);

}
