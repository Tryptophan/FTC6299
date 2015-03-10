#include "drivers\hitechnic-gyro.h";
#include "drivers\hitechnic-irseeker-v2.h"

/*
Made by Team 6299 QuadX
- Jacob Greenway
- Joshua Johnson
- Linnea May
*/
float heading = 0;

float valInRange(float val, float threshold = 1.0) {
return (abs(val) <= threshold) ? 0 : val;
}

bool isInRange(float heading, float targetHeading, float threshold = 1.0) {
	return abs(heading - targetHeading) <= threshold;
}

int getLiftAverage() {
	int divide = 2;
	if (nMotorEncoder[liftL] == 0) {
		divide--;
	}
	if (nMotorEncoder[liftR] == 0) {
		divide--;
	}
	return (((nMotorEncoder[liftL] + nMotorEncoder[liftR]) / divide) * -1);
}

int getEncoderAverage() {
	int divide = 4;
	int exclude[4] = {0, 0, 0, 0};
	int encoders[4] = {nMotorEncoder[motorFL], nMotorEncoder[motorFR], nMotorEncoder[motorBL], nMotorEncoder[motorBR]};

	/*if (nMotorEncoder[motorFL] < 40 && nMotorEncoder[motorFL] > -40) {
		divide--;
		exclude[0] = 1;
	}
	if (nMotorEncoder[motorFR] < 40 && nMotorEncoder[motorFR] > -40) {
		divide--;
		exclude[1] = 1;
	}
	if (nMotorEncoder[motorBL] < 40 && nMotorEncoder[motorBL] > -40) {
		divide--;
		exclude[2] = 1;
	}
	if (nMotorEncoder[motorBR] < 40 && nMotorEncoder[motorBR] > -40) {
		divide--;
		exclude[3] = 1;
	}*/

	int sum = 0;

	for (int j = 0; j < 4; j++) {
		if (exclude[j] == 0) {
			sum += encoders[j];
		}
	}

	return sum / divide;
}

void setMotors(int left, int right) {
	motor[motorFL] = left;
	motor[motorBL] = left;
	motor[motorFR] = right;
	motor[motorBR] = right;
}

void stopMotors() {
	motor[motorFL] = 0;
	motor[motorBL] = 0;
	motor[motorFR] = 0;
	motor[motorBR] = 0;
}

void moveTo(int power, int deg, float threshold = 2.0, long time = 100000, float cor = 4.0) {
	heading = 0;
	nMotorEncoder[motorBL] = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorBR] = 0;
	wait1Msec(250);
	clearTimer(T1);
	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage() < deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(SENSOR_GYRO), threshold) * (float)(20 / 1000.0);

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors((power / cor), power);
				}
				if (heading < 0) {
					setMotors(power, (power / cor));
				}
			}
			wait1Msec(20);
		}
	}

	else {
		while (time1[T1] < time && getEncoderAverage() > deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(SENSOR_GYRO), threshold) * (float)(20 / 1000.0);

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors(power, (power / cor));
				}
				if (heading < 0) {
					setMotors((power / cor), power);
				}
			}
			wait1Msec(20);
		}
	}

	stopMotors();
	//nxtDisplayBigTextLine(1, "%4i",heading);
}

void turn(int power, int deg, int time = 6000) {

	heading = 0;
	wait1Msec(250);
	clearTimer(T1);

	if (deg > 0) {
		while (time1[T1] < time && abs(heading) < abs(deg)) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			setMotors(power, -power);
			wait1Msec(20);
		}
	}

	if (deg < 0) {
		while (time1[T1] < time && abs(heading) < abs(deg)) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			setMotors(-power, power);
			wait1Msec(20);
		}
	}

	stopMotors();
}

void arcTurn(int power, int deg, int time = 7000) {

	// 90 Degree Modifier
	if (abs(deg) == 90) {
		int modifier = deg * 8/9;
		deg = modifier;
	}

	// 45 Degree Modifier
	else if (abs(deg) == 45) {
		int modifier = deg * 7/9;
		deg = modifier;
	}

	heading = 0;
	wait1Msec(250);
	clearTimer(T1);
	// Forward arcTurn
	if (power > 0) {
		if (deg > 0) {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}

	// Backward arcTurn (flips inequalities)
	else {
		if (deg > 0) {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && abs(heading) < abs(deg)) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}
	stopMotors();
}

void drift(int power, int deg, int angle, int time = 8000) {
	heading = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	wait1Msec(250);
	clearTimer(T1);
	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage() < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			if (angle > 0) {
				while (heading < angle) {
					setMotors(power, power - (power / 10));
				}
			}
			else {
				while (heading > angle) {
					setMotors(power - (power / 10), power);
				}
			}
		}
	}
	if (power < 0) {
		while (time1[T1] < time && getEncoderAverage() < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(20 / 1000.0);
			if (angle > 0) {
				while (heading < angle) {
					setMotors(power, power - 10);
				}
			}
			else {
				while (heading > angle) {
					setMotors(power - 10, power);
				}
			}
		}
	}
	stopMotors();
}

void latch(bool position) {
	wait1Msec(250);
	if (!position) {
		servo[servoL] = 225;
		servo[servoR] = 20;
	}
	if (position) {
		servo[servoL] = 150;
		servo[servoR] = 93;
	}
	wait1Msec(250);
}

int getPos() {
	/*int count[5] = {0, 0, 0, 0, 0};
	for (int j = 0; j < 20; j++) {
	if (HTIRS2readACDir(SENSOR_IR) == 0) {
	count[0] += 1;
	}
	if (HTIRS2readACDir(SENSOR_IR) == 1) {
	count[1] += 1;
	}
	if (HTIRS2readACDir(SENSOR_IR) == 2) {
	count[2] += 1;
	}
	if (HTIRS2readACDir(SENSOR_IR) == 3) {
	count[3] += 1;
	}
	if (HTIRS2readACDir(SENSOR_IR) == 4) {
	count[4] += 1;
	}
	delay(20);
	}
	int big = count[0];*/
	int spot = HTIRS2readACDir(SENSOR_IR);
	nxtDisplayTextLine(0, "%1i", spot);
	/*for (int j = 1; j < 5; j++) {
	if (count[j] > big) {
	spot = j;
	big = count[j];
	}
	}*/
	if (spot >= 5) {
		return 3;
	}
	else if (spot < 5 && spot >= 1) {
		return 2;
	}
	else {
		return 1;
	}
}

void lift(int power, int deg, int time = 6000) {
	nMotorEncoder[liftL] = 0;
	nMotorEncoder[liftR] = 0;
	int t = 0;
	wait1Msec(250);
	while (t < time && abs(getLiftAverage()) < deg) {
		motor[liftL] = power;
		motor[liftR] = power;
		t += 20;
		wait1Msec(20);
	}
	motor[liftL] = 0;
	motor[liftR] = 0;
}

void basket(char position) {

	if (position == 'x') {
		servo[liftServoL] = 100;
		servo[liftServoR] = 155;
	}
	if (position == 'y') {
		servo[liftServoL] = 230;
		servo[liftServoR] = 25;
	}
}

void manipulator(int time) {
	motor[flip] = -100;
	delay(time);
	motor[flip] = 0;
}

void grabMove(int power, int deg, int lat, float threshold = 2.0, long time = 100000, float cor = 4.0) {
	heading = 0;
	nMotorEncoder[motorBL] = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	nMotorEncoder[motorBR] = 0;
	wait1Msec(250);
	clearTimer(T1);
	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage() < deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(SENSOR_GYRO), threshold) * (float)(20 / 1000.0);
			if (lat < abs(getEncoderAverage())) {
				latch(true);
			}
			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors((power / cor), power);
				}
				if (heading < 0) {
					setMotors(power, (power / cor));
				}
			}
			wait1Msec(20);
		}
	}

	else {
		while (time1[T1] < time && getEncoderAverage() > deg) {

			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading += valInRange(HTGYROreadRot(SENSOR_GYRO), threshold) * (float)(20 / 1000.0);

			if (lat < abs(getEncoderAverage())) {
				latch(true);
			}
			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors(power, (power / cor));
				}
				if (heading < 0) {
					setMotors((power / cor), power);
				}
			}

			wait1Msec(20);
		}
	}
	stopMotors();
	if(lat > getEncoderAverage()) {
		latch(true);
	}
}

task liftTaskC() {
	manipulator(600);
	lift(60, 3450);
	stopTask(liftTaskC);
}

task liftTaskB() {
	lift(60, 1975);
	basket('x');
	stopTask(liftTaskB);
}

task debug(){
	float timee = 0;
		writeDebugStreamLine("--------------------------Start--------------------------");
	while(true) {
		writeDebugStreamLine("Time: %2f", timee);
		writeDebugStreamLine("\n");
		writeDebugStreamLine("BaseFL: %6i", nMotorEncoder[motorFL]);
		writeDebugStreamLine("BaseFR: %6i", nMotorEncoder[motorFR]);
		writeDebugStreamLine("BaseBL: %6i", nMotorEncoder[motorBL]);
		writeDebugStreamLine("BaseBR: %6i", nMotorEncoder[motorBR]);
		writeDebugStreamLine("\n");

		writeDebugStreamLine("LiftL: %6i", nMotorEncoder[liftL]);
		writeDebugStreamLine("LiftR: %6i", nMotorEncoder[liftR]);

		writeDebugStreamLine("\n\n");
		wait10Msec(10);
		timee += .1;
	}
}
