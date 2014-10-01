#include "Encoder.h";
#include "Gyro.h";
#include "UltraSound.h";
#include "Infared.h";
#include "Servo.h";

// Global Bucket Servo Positions
int posA = 160;
int posB = 110;
int posX = 60;
int posY = 190;

string smuxPower = "Bad";

void initializeRobot() {
	servo[servoR] = posA;
	servo[servoArm] = 230;
	servo[ratchetL] = 135;
	servo[ratchetR] = 90;

	nMotorEncoder[motorBR] = 0;
	nMotorEncoder[motorBL] = 0;

	encoder = 0;
	ultra = 255;
}

int tmp, basket = 0;

task readVars() {
	nVolume = 4;
	while(true) {
		encoder = (nMotorEncoder[motorBL] + nMotorEncoder[motorBR]) / 2;
		tmp = USreadDist(LGUS);
		ultra = tmp * .1 + ultra * .9;
		infaredL = HTIRS2readACDir(HTIRS2);
		infaredR = HTIRS2readACDir(HTIRS3);
		if (infaredR > 9)
			infaredR = 0;
		if (infaredL > 9)
			infaredL = 0;

		if (nAvgBatteryLevel < 8200)
			PlaySound(soundBlip);
		if (HTSMUXreadPowerStatus(SMUX)) {
			PlaySound(soundException);
			smuxPower = "Bad";
		}
		else {
			smuxPower = "Good";
		}
		wait1Msec(5);
	}
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void autonomous(int delay, int park) {
	wait10Msec(delay * 100);

	moveTo(200, 50);
	arcTurn(-15, 75);
	waitForWall(65, 20);
	int dir = leftOrRight();

	// Move to ir beacon and record basket number
	if (dir > 0)
		turn(66, 35);
	if (dir < 0)
		turn(65, 35);
	if (dir < 0) {
		moveTo(-1200, 50);
		wait10Msec(50);
		if(infaredL == 5) {
			moveTo(700, 50);
		}
		else {
			basket = 1;
			moveTo(100, 50);
		}
	}

	if (dir > 0) {
		moveTo(150, 50);
		wait10Msec(50);
		if (infaredL == 5) {
			moveTo(400, 50);
		}
		else {
			moveTo(1100, 50);
			basket = 1;
		}
	}

	// Dump block in basket
	servo[servoArm] = 0;
	wait10Msec(50);
	servo[servoArm] = 230;

	// Move away from baskets
	if (dir < 0) {
		if (basket == 0)
			moveTo(-1000, 50);
		else if (basket == 1)
			moveTo(-600, 50);
	}

	if (dir > 0) {
		if (basket == 0)
			moveTo(800, 50);
		else if (basket == 1)
			moveTo(200, 50);
	}

	// Turn and park on ramp if ir beacon is on left side
	time1[T1] = 0;
	float delTime = 0;
	float prevTime = 0;
	int rotSpeed;
	if (dir < 0) {
		heading = 0;
		while (heading < 30) {
			delTime = ( ((float)time1[T1]) - prevTime ) / 1000;
	  	prevTime = ((float)time1[T1]);

	    // Read the current rotation speed
	    rotSpeed = HTGYROreadRot(HTGR);
	    heading += rotSpeed * delTime;
			setMotors(0, 0, -75, -75);
		}
		stopMotors();

		moveTo(-2600, 50);
		delTime = 0;
		prevTime = 0;
		rotSpeed = 0;
		if (dir < 0) {
			heading = 0;
			while (heading < 110) {
				delTime = ( ((float)time1[T1]) - prevTime ) / 1000;
		  	prevTime = ((float)time1[T1]);

		    // Read the current rotation speed
		    rotSpeed = HTGYROreadRot(HTGR);
		    heading += rotSpeed * delTime;
				setMotors(0, 0, -75, -75);
			}
			stopMotors();
		}
		if (park <= 0)
			moveTo(-4000, 50);
		if (park > 0)
			moveTo(-5000, 50);
	}

	// If ir beacon is on right side ramp park
	if (dir > 0) {
		arcTurn(-35, 75);
		moveTo(2600, 50);
		turn(60, 35);
		if (park >= 0)
			moveTo(-4000, 50);
		if (park < 0)
			moveTo(-6000, 50);
	}
}

// Parks on the ramp backwards and dum the block
void autoBackDump(int delay) {
	wait10Msec(delay * 100);
	moveTo(-1600, 50);

	time1[T1] = 0;
	float delTime = 0;
	float prevTime = 0;
	int rotSpeed;
	heading = 0;
	while (heading < 25) {
		delTime = ( ((float)time1[T1]) - prevTime ) / 1000;
  	prevTime = ((float)time1[T1]);

    // Read the current rotation speed
    rotSpeed = HTGYROreadRot(HTGR);
    heading += rotSpeed * delTime;
		setMotors(0, 0, -75, -75);
	}
	stopMotors();

	moveTo(-800, 50);

	servo[servoArm] = 0;
	wait10Msec(50);
	servo[servoArm] = 230;

	moveTo(-2200, 50);
}

void autoFrontDump(int delay) {
	wait10Msec(delay * 100);
	moveTo(1600, 50);
	arcTurn(-25, 75);
	moveTo(1000, 50);
	servo[servoArm] = 0;
	wait10Msec(50);
	servo[servoArm] = 230;
	moveTo(1800, 50);
}
