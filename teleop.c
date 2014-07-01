#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";



task driveControl() {
	while (true) {
		getJoystickSettings(joystick);
		if (abs(joystick.joy1_y1) > 10 || abs(joystick.joy1_y2) > 10) {
				motor[motorFL] = joystick.joy1_y1 / 1.28;
				motor[motorBL] = joystick.joy1_y1 / 1.28;
				motor[motorFR] = joystick.joy1_y2 / 1.28;
				motor[motorBR] = joystick.joy1_y2 / 1.28;
		}

		else {
			motor[motorBL] = 0;
			motor[motorBR] = 0;
		}
	}
}

task main () {
	StartTask(driveControl);
	while(true){}
}
