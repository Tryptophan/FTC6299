#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     SENSOR_IR,      sensorNone)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorR,        tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "libs.h";
//#include "autonomous_methods.h";
#include "drivers\JoystickDriver.c";

task main(){
	turn(10, 90);
	while(true){}
}
