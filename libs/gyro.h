#include "libs/drivers/hitechnic-gyro.h";
// Gyro Stabalization Psuedocode
float heading = 0;

float valInRange(float val, float threshold = 1.0) {
	return abs(val) <= threshold ? 0 : val;
}

bool isInRange(float heading, float targetHeading, float threshold = 1.0) {
	return abs(heading - targetHeading) <= threshold;
}

int getDriveDir(int power) {
	return (power > 0) ? 1 : (power < 0) ? -1 : 0;
}

int getTurnPower(int power) {
	return (power < 0) ? power - 50 : (power > 0) ? power + 50 : 0;
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

void drive(int power, int time) {
	time1[T1] = 0;
	HTGYROstartCal(SENSOR_GYRO);
	heading = 0;
	while (time1[T1] < time) {
		heading += valInRange(HTGYROreadRot(SENSOR_GYRO), 2.0) * (float)(time1[T1] / 1000.0);
		if (!isInRange(heading, 0, 2.0)) {
			if (heading > 0)
				setMotors(power - 20 * getDriveDir(power), power);
			else
				setMotors(power, power - 20 * getDriveDir(power));
		}
		else
			setMotors(power, power);
		wait1Msec(10);
	}
	stopMotors();
}

void turn(int power, int deg, int time = 2000) {
	time1[T1] = 0;
	if (deg > 0) {
		while (time1[T1] < time && heading < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
			setMotors(power, -power);
			wait1Msec(10);
		}
	}

	else {
		while (time1[T1] < time && heading < deg) {
			heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
			setMotors(-power, power);
			wait1Msec(10);
		}
	}
	stopMotors();
}

void arcTurn(int power, int deg, int time = 2000) {
	time1[T1] = 0;

	// Forward arcTurn
	if (power > 0) {
		if (deg > 0) {
			while (time1[T1] < time && heading < deg) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
				setMotors(power, 0);
				wait1Msec(10);
			}
		}

		else {
			while (time1[T1] < time && heading > deg) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
				setMotors(0, power);
				wait1Msec(10);
			}
		}
	}

	// Backward arcTurn (flips inequalities)
	else {
		if (deg > 0) {
			while (time1[T1] < time && heading > deg) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
				setMotors(power, 0);
				wait1Msec(10);
			}
		}

		else {
			while (time1[T1] < time && heading < deg) {
				heading += HTGYROreadRot(SENSOR_GYRO) * (float)(time1[T1] / 1000.0);
				setMotors(0, power);
				wait1Msec(10);
			}
		}
	}
	stopMotors();
}
