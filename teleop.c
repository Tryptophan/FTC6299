#include "JoystickDriver.c";

void calibrateControllers() {
	// Calibrate controller 1
	const int CONTROLLER1_JOYSTICK1_X = (joystick.joy1_x1) * -1;
	const int CONTROLLER1_JOYSTICK1_Y = (joystick.joy1_y1) * -1;
	const int CONTROLLER1_JOYSTICK2_X = (joystick.joy1_x2) * -1;
	const int CONTROLLER1_JOYSTICK2_Y = (joystick.joy1_y2) * -1;

	// Calibrate controller 2
	const int CONTROLLER2_JOYSTICK1_X = (joystick.joy2_x1) * -1;
	const int CONTROLLER2_JOYSTICK1_Y = (joystick.joy2_y1) * -1;
	const int CONTROLLER2_JOYSTICK2_X = (joystick.joy2_x2) * -1;
	const int CONTROLLER2_JOYSTICK2_Y = (joystick.joy2_y2) * -1;
}

task driveControl () {
	while (true) {
		getJoystickSettings(joystick);
	}

	
}


task main () {
	calibrateControllers();
	StartTask(driveControl);
}