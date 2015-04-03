#include "libs.h";

void initializeRobot() {
	nVolume = 4;
	latch(false);
	basket('y');
	fLatch(false, false);
}

// Finds the ir beacon, dumps the block, and parks on the ramp
void bare(int s, int position, int tube) {
	delay(s * 1000);
	if (tube == 2) {
		/*if (position == 1) {  //Parking Zone
			playSound(soundBeepBeep);
			moveTo(-25, -1243, 1.5);
			turn(-25, -21);
			moveTo(-25, -3885, 1.5);
			turn(-20, -50);
			moveTo(-25, -3900, 10.0, 2250);
			moveTo(25, 1010);
			turn(-25, 55);
			moveTo(-20, -1700, 1.5);
			latch(true);
			moveTo(20, 1087, 1.5);
			turn(25, 190);
			moveTo(-50, -5439, 1.5);
			lift(60, 2000);
			basket('x');
		}*/
		if (position == 0) {  //Ramp
			playSound(soundBeepBeep);
			moveTo(-30, -4800, 1.0);
			turn(50, -45);
			moveTo(-30, -850, 1.5);
			turn(50, 90);
			grabMove(-25, -1000, 900, 1.5);
			startTask(liftTaskB);
			delay(3000);
			startTask(retractTaskB);
			turn(50, -80);
			moveTo(-30, -900, 1.5);
			latch(false);
			moveTo(30, 980, 1.5);
			turn(40, 50);
			grabMove(-35, -1000, 900, 1.5);
			startTask(liftTaskC);
			arcTurn(40, 95);
			fLatch(true, false);
			arcTurn(50, 20);
			fLatch(true, true);
			startTask(retractTaskC);
		}
	}
	if (tube == 1) {
		/*if (position == 0) {
			playSound(soundBeepBeep);
			moveTo(-15, -5050, 1.25, 4000);
			turn(25, -45);
			moveTo(-30, -1870, 1.0);
			turn(25, 46);
			moveTo(-25, -1600, 1.0);
			latch(true);
			moveTo(30, 4000, 1.0);
			turn(25, 60);
			moveTo(25, 375, 1.0);
			turn(25, 145);
			moveTo(-80, -3799, 1.5);
			lift(60, 1270);
			basket('x');
			latch(false);
		}*/
	}
	playSound(soundDownwardTones);
}

void center(int s, int position) {
	if (position == 0) {
		moveTo(25, 1600, 0.4);
		int irPosition = getPos();
		//writeDebugStreamLine("%1i", irPosition);
		if(irPosition == 3 || irPosition == 1) {
			//writeDebugStreamLine("%1i", getPos();
			moveTo(25, 600, 0.4);
			if (ready) {
				displayTextLine(02, "%4f", irVal);
				if (irVal >= 4.0) {
					irPosition = 3;
				}
				else {
					irPosition = 1;
				}
			}
			/*if (HTIRS2readACDir(SENSOR_IR) >= 2) {
				nxtDisplayTextLine(0, "%1i", HTIRS2readACDir(SENSOR_IR));
				moveTo(-25, -400, 0.4);
				irPosition = 3;
			}
			else if (HTIRS2readACDir(SENSOR_IR) < 2) {
				nxtDisplayTextLine(0, "%1i", HTIRS2readACDir(SENSOR_IR));
				moveTo(-25, -720, 0.4);
				irPosition = 1;
			}*/
		}
		//displayTextLine(0, "%1i", getPos());
		if (irPosition == 3) {
			turn(30, 90);
			moveTo(-50, -750, 0.4); //350
			turn(30, 90);
			moveTo(-50, -1400, false);
			moveTo(50, 150);
		}
		else if (getPos() == 2) {
			moveTo(40, 200, 0.4);
			arcTurn(-50, -120);
			moveTo(-40, -1890, 0.4);
			turn(30, 100); //Turn perpendicular to goal
			moveTo(-30, -1200, false); //Ram the goal
			moveTo(20, 90); //Move back from the goal
		}
		else if (irPosition == 1) {
			turn(-35, -115);
			moveTo(-50, -3000, 0.4);
			turn(-35, -45);
			moveTo(-35, -1100, 0.4);
			turn(35, 95);
			moveTo(-40, -900, false);
			moveTo(50, 180);
		}
		lift(60, 4775, 3500);
		basket('x');
		delay(2500);
		basket('y');
		lift(-60, 5000, 3500);
		arcTurn(50, -90);
		moveTo(30, 200);
		arcTurn(50, -100);
		moveTo(80, 2300);
		arcTurn(50, -95);
	}
	writeDebugStreamLine("End");
}

void kick(int suspend){
	delay(suspend * 100);

}
