#include "libs.h";

void initializeRobot() {
	nVolume = 4;
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void bare(int suspend, int begin) {
	wait10Msec(suspend * 100);
	if (begin == 1){
		playSound(soundBeepBeep);
	}
	if (begin == 0){
		playSound(soundDownwardTones);
	}
	playSound(soundBeepBeep);
}

void autoFrontDump(int suspend) {
	wait10Msec(suspend * 100);

}

void test(int suspend){
	wait10Msec(suspend * 100);

}
