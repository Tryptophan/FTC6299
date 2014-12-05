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
		moveTo(-15, -1600, 1.5);
		turn(-20, -21);
		moveTo(-15, -5000, 1.5);
		turn(-20, -50);
		moveTo(-15, -2000, 1.5, 2000);
		moveTo(15, 1300);
		turn(-20, 60);

		/*
		latch(true);
		moveTo(15, 1100, 1.5);
		turn(20, 180);
		moveTo(-40, -7000, 1.5);
		//lift(60, 2000);
		//basket('x');
		latch(false);*/
	}
	if (position == 0) {  //Ramp
		playSound(soundBeepBeep);
		moveTo(-10, -6300, 1.5, 4000);
		turn(20, -45);
		moveTo(-15, -900);
		turn(-20, -80);
		moveTo(-15, -1100, 2.0);
		latch(true);
		moveTo(15, 900);
		turn(20, 165);
		moveTo(-40, -7100, 2.0);
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
