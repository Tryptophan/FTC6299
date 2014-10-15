#include "drivers\hitechnic-gyro.h";

float heading = 0;

//Support method that sends the command to Arduino for heading
int sendArduinoCommand(unsigned char command)
{
	signed int result;
	HTSPBsetupIO(HTSPB, 0xFF); //sets B0-7 to output
	HTSPBwriteStrobe(HTSPB, command); // send the command via S0-3
	if (command >= 2)
	{
		HTSPBsetupIO(HTSPB, 0x00); // sets BO-7 to input so that it can receive
		result = HTSPBreadIO(HTSPB, 0xFF);
	}
	return result;
}

//Get the current heading from the MPU6050 gyro
int getMPUHeading()
{
	int add1 = sendArduinoCommand(2);
	int MPUheading = add1 * 2; 
	if(MPUheading > 180)
		MPUheading = heading - 360; 
	return MPUheading;
}

float valInRange(float val, float threshold = 1.0) {
	return (abs(val) <= threshold) ? 0 : val;
}

bool isInRange(float heading, float targetHeading, float threshold = 1.0) {
	return abs(heading - targetHeading) <= threshold;
}

int getDriveDir(int power) {
	return (power > 0) ? 1 : (power < 0) ? -1 : 0;
}

int getEncoderAverage(int leftMotor, int rightMotor) {
	return (leftMotor == 0) ?	rightMotor : (rightMotor == 0) ? leftMotor : (leftMotor + rightMotor) / 2;
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

void moveTo(int power, int deg, float threshold = 2.0, long time = 5000) {
	heading = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;

	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);

	clearTimer(T1);

	if (power > 0) {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorBL]) < deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading = getMPUHeading();

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors((power / 4) * getDriveDir(power), power);
				}
				if (heading < 0) {
					setMotors(power, (power / 4) * getDriveDir(power));
				}
			}

			wait1Msec(20);
		}
	}

	else {
		while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorFL], nMotorEncoder[motorFR]) > deg) {
			// Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
			heading = getMPUHeading;

			// Checks if the gyro is outside of the specified threshold (1.0)
			if (isInRange(heading, 0, threshold)) {
				setMotors(power, power);
			}

			// If not, lower the speed of the required side of the robot to adjust back to 0
			else {
				if (heading > 0) {
					setMotors(power, (power / 4) * getDriveDir(power));
				}
				if (heading < 0) {
					setMotors((power / 4) * getDriveDir(power), power);
				}
			}

			wait1Msec(20);
		}
	}

	stopMotors();
}

void turn(int power, int deg, int time = 5000) {
	// 90 Degree Modifier
	if (deg == 90) {
		int modifier = deg * 8/9;
		deg = modifier;
	}
	else if (deg == 45) {
		int modifier = deg * 7/9;
		deg = modifier;
	}

	heading = 0;

	wait1Msec(500);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(500);

	clearTimer(T1);

	if (deg > 0) {
		while (time1[T1] < time && heading < deg) {
			heading = getMPUHeading;
			setMotors(power, -power);
			wait1Msec(20);
		}
	}

	else {
		while (time1[T1] < time && heading < deg) {
			heading = getMPUHeading;
			setMotors(-power, power);
			wait1Msec(20);
		}
	}
	stopMotors();
}

void arcTurn(int power, int deg, int time = 2000) {
	heading = 0;
	clearTimer(T1);
	HTGYROstartCal(SENSOR_GYRO);

	// Forward arcTurn
	if (power > 0) {
		if (deg > 0) {
			while (time1[T1] < time && heading < deg) {
				heading = getMPUHeading;
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && heading > deg) {
				heading = getMPUHeading;
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}

	// Backward arcTurn (flips inequalities)
	else {
		if (deg > 0) {
			while (time1[T1] < time && heading > deg) {
				heading = getMPUHeading;
				setMotors(power, 0);
				wait1Msec(20);
			}
		}

		else {
			while (time1[T1] < time && heading < deg) {
				heading = getMPUHeading;
				setMotors(0, power);
				wait1Msec(20);
			}
		}
	}
	stopMotors();
}
