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

int getEncoderAverage(int leftMotor, int rightMotor) {
	if (abs(leftMotor) < 3) {
		return rightMotor;
	}
	if (abs(rightMotor) < 3) {
		return leftMotor;
	}
	return (leftMotor + rightMotor) / 2;
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

void moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0) {
	heading = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);

	clearTimer(T1);

	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorBL]) < deg) {
			displayCenteredBigTextLine(3, "%10i", nMotorEncoder[motorFL]);
			displayCenteredBigTextLine(5, "%10i", nMotorEncoder[motorFR]);
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
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) > deg) {
			displayCenteredBigTextLine(3, "%10i", nMotorEncoder[motorFL]);
			displayCenteredBigTextLine(5, "%10i", nMotorEncoder[motorFR]);
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
}

void turn(int power, int deg, int time = 5000) {

	/*// 90 Degree Modifier
	if (abs(deg) == 90) {
		int modifier = deg * 8/9;
		deg = modifier;
	}

	// 45 Degree Modifier
	else if (abs(deg) == 45) {
		int modifier = deg * 7/9;
		deg = modifier;
	}*/

	heading = 0;

	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);

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

void arcTurn(int power, int deg, int time = 3000) {

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
	clearTimer(T1);
	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);
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

void latch(bool position) {
	if (!position) {
		servo[servoL] = 225;
		servo[servoR] = 0;
	}
	if (position) {
		servo[servoL] = 150;
		servo[servoR] = 93;
	}
}

int getPos() {
	wait1Msec(175);
	if(HTIRS2readACDir(SENSOR_IR) == 3)
		return 1;
	if(HTIRS2readACDir(SENSOR_IR) == 5)
		return 2;
	if(HTIRS2readACDir(SENSOR_IR) == 0)
		return 3;
	return 0;
}

void lift(int power, int time) {
	int t = 0;
	while (t < time) {
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
