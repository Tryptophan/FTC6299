#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     SENSOR_IR,      sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "libs.h";
#include "autonomous_chooser.h";
//#include "autonomous_methods.h";
#include "drivers\JoystickDriver.c";


task main(){
	while(true){
		MPUheading = getMPUHeading();
		nxtDisplayBigTextLine(1, "%d", MPUheading); //it takes a full 4 seconds to get heading....
	}
		moveTo(20, 300, 60000);
}
