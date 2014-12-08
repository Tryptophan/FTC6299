#include "libs.h";

void initializeRobot() {
	nVolume = 4;
	latch(false);
	basket('y');
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void bare(int s, int position) {
	delay(s * 1000);
	if (position == 1) {  //Parking Zone
		playSound(soundBeepBeep);
		moveTo(-15, -1243, 1.5);
		turn(-20, -21);
		moveTo(-15, -3885, 1.5);
		turn(-20, -50);
		moveTo(-15, -1709, 1.5, 2250);
		moveTo(15, 1010);
		turn(-20, 55);
		moveTo(-15, -1554);
		latch(true);
		moveTo(15, 1087, 1.5);
		turn(20, 190);
		moveTo(-15, -5439, 1.5);
		lift(60, 2000);
		basket('x');
		latch(false);
	}
	if (position == 0) {  //Ramp
		playSound(soundBeepBeep);
		moveTo(-10, -4895, 1.5, 4000);
		turn(20, -45);
		moveTo(-15, -699);
		turn(-20, -80);
		moveTo(-15, -854, 2.0);
		latch(true);
		moveTo(15, 700);
		turn(20, 165);
		moveTo(-40, -5516, 2.0);
		lift(60, 2100);
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
