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
	motor[motorL] = left;
	motor[motorR] = right;

}

void stopMotors() {
	motor[motorL] = 0;
	motor[motorR] = 0;
}

void moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0) {
	heading = 0;
	nMotorEncoder[motorL] = 0;
	nMotorEncoder[motorR] = 0;

	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);

	clearTimer(T1);

	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorL], nMotorEncoder[motorL]) < deg) {
			displayCenteredBigTextLine(3, "%10i", nMotorEncoder[motorL]);
			displayCenteredBigTextLine(5, "%10i", nMotorEncoder[motorR]);
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
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorL], nMotorEncoder[motorR]) > deg) {
			displayCenteredBigTextLine(3, "%10i", nMotorEncoder[motorL]);
			displayCenteredBigTextLine(5, "%10i", nMotorEncoder[motorR]);
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
