#include "libs.h";

void initializeRobot() {
	nVolume = 4;
	latch(false);
	basket('y');
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
			moveTo(-35, -4800, 1.5);
			turn(50, -45);
			moveTo(-30, -1200, 1.5);
			turn(-50, -90);
			grabMove(-25, -1000, 870, 1.5);
			startTask(liftTaskB);
			moveTo(50, 200, 1.5);
			turn(-45, -75);
			delay(2000);
			basket('y');
			moveTo(-40, -300, 1.5);
			lift(-60, 2300); //2400
			latch(false);
			moveTo(40, 400, 1.5);
			turn(-60, 30);
			moveTo(-50, -1100, 30.0);
			moveTo(40, 100);
			turn(-30, 85);
			grabMove(-40, -750, 600, 1.5);
			moveTo(50, 800);
			turn(-35, 135); //42
			startTask(liftTaskC);
			moveTo(-100, -5800);
			delay(500);
			basket('x');
			delay(2000);//1500
			moveTo(-100, -600);
			basket('y');
			lift(-60, 3900);
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
		moveTo(15, 1600, 0.4);
		int irPosition = getPos();
		//writeDebugStreamLine("%1i", irPosition);
		if(irPosition == 3 || irPosition == 1) {
			//writeDebugStreamLine("%1i", getPos();
			moveTo(15, 1200, 0.4);
			if (getPos() == 3) {
				moveTo(-15, -600, 0.4);
			}
			else if (getPos() == 1) {
				moveTo(-15, -600, 0.4);
			}
		}
		//displayTextLine(0, "%1i", getPos());
		if (getPos() == 3) {
			turn(30, 80);
			moveTo(-50, -350, 0.4); //350
			turn(30, 70);
			moveTo(-50, -1400);
			moveTo(50, 50);
		}
		else if (getPos() == 2) {
			arcTurn(-50, -120);
			moveTo(-40, -1715, 0.4);
			turn(30, 75);
			moveTo(-30, -1200);
			moveTo(53, 60);
		}
		else if (getPos() == 1) {
			turn(-35, -100);
			moveTo(-50, -2800, 0.4);
			turn(-35, -45);
			moveTo(-35, -400, 0.4); //500
			turn(35, 70);
			moveTo(-40, -1050);
			moveTo(50, 100); //120
		}
		lift(60, 4500, 3500);
		basket('x');
		delay(2500);
		basket('y');
		lift(-60, 5000, 3500);
		arcTurn(50, -90);
		moveTo(30, 200);
		arcTurn(50, -95);
		moveTo(80, 1500);
	}
	writeDebugStreamLine("End");
}

void kick(int suspend){
	delay(suspend * 100);

}
