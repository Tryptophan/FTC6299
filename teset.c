#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     SENSOR_IR,      sensorI2CCustom)
#pragma config(Sensor, S2,     SENSOR_GYRO,    sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     motorFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     motorFR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     liftL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     liftR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C4_1,     flip,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    servoL,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servoR,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    liftServoL,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    liftServoR,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers\hitechnic-gyro.h";

task main()
{
	int base = 0;
	nMotorEncoder[motorFL] = 0;
	nMotorEncoder[motorFR] = 0;
	while (true) {
		while (base == 0) {
			displayTextLine(0, "Lift");
			while (nNxtButtonPressed == 1) {
				motor[liftL] = 100;
				motor[liftR] = 100;
			}
			while (nNxtButtonPressed == 2) {
				motor[liftL] = -70;
				motor[liftR] = -70;
			}
			motor[liftL] = 0;
			motor[liftR] = 0;
			if (nNxtButtonPressed == 3) {
				base++;
				delay(500);
			}
		}
		while (base == 1) {
			displayTextLine(0, "Base");
			displayTextLine(1, "EncoderL: %6i", nMotorEncoder[motorFL]);
			displayTextLine(2, "EncoderR: %6i", nMotorEncoder[motorFR]);
			while (nNxtButtonPressed == 1) {
				motor[motorFL] = 100;
				motor[motorFR] = 100;
				motor[motorBL] = 100;
				motor[motorBR] = 100;
			}
			while (nNxtButtonPressed == 2) {
				motor[motorFL] = -100;
				motor[motorFR] = -100;
				motor[motorBL] = -100;
				motor[motorBR] = -100;
			}
			displayTextLine(3, "GyroROT: %2i", HTGYROreadRot(SENSOR_GYRO));
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorBR] = 0;
			motor[motorFR] = 0;
			if (nNxtButtonPressed == 3) {
				base++;
				delay(500);
			}
		}
		while (base == 2) {
			displayTextLine(0, "Flinger Flanger");
			while (nNxtButtonPressed == 1) {
				motor[flip] = 100;
			}
			while (nNxtButtonPressed == 2) {
				motor[flip] = -100;
			}
			motor[flip] = 0;
			if (nNxtButtonPressed == 3) {
				base = 0;
				delay(500);
			}
		}
	}
	while(true){}
}
