#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S2,     SENSOR_GYRO,    sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     SENSOR_IR,      sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftR,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     flip,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    servoL,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servoR,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    liftServoL,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    liftServoR,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "libs.h";
#include "autonomous_chooser.h";
#include "autonomous_methods.h";
#include "drivers\JoystickDriver.c";

/*
	Made by Team 6299 QuadX
		- Jacob Greenway
		- Joshua Johnson
		- Linnea May
*/

task main(){

	//Starts Autonomous Chooser
	startTask(chooser);
	waitForStart();

	stopTask(chooser);

	// Set and run desired autonomous program
	switch(i) {
		case 0 :
			bare(suspend, begin);
			break;
		case 1 :
			autoFrontDump(suspend);
		case 2 :
			test(suspend);
			break;
}
	while(true){}
}
