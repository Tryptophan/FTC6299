#include "libs.h";

void initializeRobot() {
	nVolume = 4;
	latch(false);
	basket('y');
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void bare(int s, int position) {
	delay(s * 100);
	if (position == 1) {  //Parking Zone
		playSound(soundBeepBeep);
		moveTo(-15, -1200, 1.5);
		arcTurn(-20, -25);
		moveTo(-15, -7200, 1.5);
		latch(true);
		moveTo(15, 1100, 1.5);
		turn(20, 80);
		turn(20, 90);
		moveTo(-15, -7000, 1.5);
		lift(60, 2000);
		basket('x');
		delay(3000);
		latch(false);
	}
	if (position == 0) {  //Ramp
		playSound(soundBeepBeep);
		moveTo(-10, -7600, 1.5);
		latch(true);
		arcTurn(20, 30);
		moveTo(15, 900, 0.8, 2000);
		turn(20, 80);
		turn(20, 90);
		moveTo(-25, -7000, 2.0, 7000);
		lift(60, 2000);
		basket('x');
		latch(false);
	}
}

void autoFrontDump(int s) {
	delay(s * 100);
	basket('x');
}

void test(int suspend){
	delay(suspend * 100);

}
