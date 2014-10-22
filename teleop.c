#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     SENSOR_GYRO,    sensorNone)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
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
#pragma config(Servo,  srvo_S3_C1_3,    liftServoL,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_4,    liftServoR,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";
task flipperFlapper(){
	while(true){
		while(joy1Btn(07) == 1){
			motor[flip] = 100;
		}
		while(joy1Btn(08) == 1){
			motor[flip] = -100;
		}
	motor[flip] = 0;
	wait10Msec(5);
	}
}
task driveControl() {
	bool slowmo = false;
	while (true) {
		getJoystickSettings(joystick);
		if ((abs(joystick.joy1_y1) > 10 || abs(joystick.joy1_y2) > 10) && !slowmo) {
				motor[motorFL] = joystick.joy1_y1 / 1.28;
				motor[motorBL] = joystick.joy1_y1 / 1.28;
				motor[motorFR] = joystick.joy1_y2 / 1.28;
				motor[motorBR] = joystick.joy1_y2 / 1.28;
		}
		else if ((abs(joystick.joy1_y1) > 10 || abs(joystick.joy1_y2) > 10) && slowmo) {
				motor[motorFL] = joystick.joy1_y1 / 4.28;
				motor[motorBL] = joystick.joy1_y1 / 4.28;
				motor[motorFR] = joystick.joy1_y2 / 4.28;
				motor[motorBR] = joystick.joy1_y2 / 4.28;
		}
		else {
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
		if (joystick.joy1_TopHat == 0) {
			slowmo = false;
		}
		if (joystick.joy1_TopHat == 4) {
			slowmo = true;
		}
	}
}

task servos()
{
	while(true)
	{
		if(joy1Btn(05) == 1)
		{
			servo[servoL] = 250;
			servo[servoR] = 0;
		}
		if(joy1Btn(06) == 1)
		{
			servo[servoL] = 160;
			servo[servoR] = 90;
		}
		while(joy2Btn(05) == 1)
		{
			servo[liftServoL] = 90;
			servo[liftServoL] = 164;
		}
		while(joy2Btn(06) == 1)
		{
			servo[liftServoL] = 164;
			servo[liftServoL] = 90
		}
	servo[liftServoL] = 127;
	servo[liftServoR] = 127;
	}
}

task slide()
{
	while(true){
		while(abs(joystick.joy2_y2) >= 10){
			motor[liftL] = joystick.joy2_y2 / 1.28;
			motor[liftR] = joystick.joy2_y2 / 1.28;
		}
		motor[liftL] = 0;
		motor[liftR] = 0;
	}
}
task main () {
	waitForStart();
	startTask(driveControl);
	startTask(servos);
	startTask(flipperFlapper);
	startTask(slide);
	while(true){}
}
