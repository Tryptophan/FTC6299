
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
		moveTo(-10, -7300, 2.1);
		latch(true);
		arcTurn(17, 23);
		moveTo(15, 1300, 0.8);
		turn(15, 90);
		turn(15, 90);
		moveTo(-25, -6000, 2.0);
		latch(false);
	}

}

void autoFrontDump(int suspend) {
	wait10Msec(suspend * 100);

}

void test(int suspend){
	wait10Msec(suspend * 100);

}
