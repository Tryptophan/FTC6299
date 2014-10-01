#include "libs.h";


// Global Bucket Servo Positions
int posA = 160;
int posB = 110;
int posX = 60;
int posY = 190;

string smuxPower = "Bad";

void initializeRobot() {

}

int tmp, basket = 0;



// Finds the ir beacon, dumps the block, and parks on the ramp
void autonomous(int suspend, int park) {
	wait10Msec(suspend * 100);

}

void autoFrontDump(int suspend) {

}
