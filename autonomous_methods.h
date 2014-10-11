
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
		moveTo(-20, -7000, 5.0);
		latch(true);
		arcTurn(20, 25);
		moveTo(30, 1000, 0.8);
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
