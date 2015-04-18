#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     SENSOR_IR,      sensorI2CCustom)
#pragma config(Sensor, S2,     SENSOR_GYRO,    sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     motorFL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     motorBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C2_2,     motorBR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C3_1,     liftL,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C3_2,     liftR,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C4_1,     flip,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    servoL,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servoR,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    liftServoL,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    liftServoR,           tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    kickL,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    kickR,                tServoStandard)
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

	// Starts Autonomous Chooser
	nVolume = 4;
	startTask(chooser);
	waitForStart();
	stopTask(chooser);
	startTask(irReads);
	//startTask(debug);
	wait1Msec(50);
	HTGYROstartCal(SENSOR_GYRO);
	wait1Msec(50);


	// Set and run desired autonomous program
	switch(i) {
	case 0 :
		bare(suspend, begin, tube);
		break;
	case 1 :
		center(suspend, begin);
		break;
	case 2 :
		kick(suspend);
		break;
	}
	//stopTask(debug);
	writeDebugStreamLine("---------------------------End---------------------------");
	while(true){}
}\
