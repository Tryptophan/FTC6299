#include "drivers\hitechnic-gyro.h";
#include "drivers\hitechnic-irseeker-v2.h";
#include "drivers\hitechnic-superpro.h";

float heading; // = 0;

/*
												sendArduinoCommand():
Supporting method for getMPUHeading() and getMPUAccel()
Command numbers correlate with different functions compiled to the Arduino

Command 1: Tell the arduino to blink LED (debug)

Command 2: Receive the first half of heading from the arduino
Command 3: Receive the second half of heading from the arduino
NOTE: To receive the full heading, call getMPUHeading(), which
bitwise or pairs the values to return actual heading.


Command 4: receive raw acceleration on the x axis
(Command 5: receive the second half of raw acceleration from the arduino)
NOTE: To receive full acceleration, call getMPUAccel(), which bitwise
or pairs the two values to return the actual heading.

Command 6: Receive raw values from the arduino
Command 7: Receive second half of raw x values from arduino
*/

signed int sendArduinoCommand(unsigned char command)
{
	signed int result;
	HTSPBsetupIO(HTSPB, 0xFF); //sets B0-7 to output
	HTSPBwriteStrobe(HTSPB, command); // send the command via S0-3
	if (command >= 2)
	{
		HTSPBsetupIO(HTSPB, 0x00); // sets BO-7 to input so that it can receive
		result = HTSPBreadIO(HTSPB, 0xFF);
	}
	return result;
}

//Get the current heading from the MPU6050 gyro
short getMPUHeading()
{
	signed char add1 = sendArduinoCommand(2);
	signed char add2 = sendArduinoCommand(3);
	short MPUheading = add1 | (add2 << 8);
	return MPUheading;
}

short getMPUAccelX()
{
	signed char raw = sendArduinoCommand(4);
	signed char raw2 = sendArduinoCommand(5);
	return raw | (raw2 << 8);
}

short getMPUrot()
{
	signed char half1 = sendArduinoCommand(6);
	signed char half2 = sendArduinoCommand(7);
	return half1 | (half2 << 8);
}

float valInRange(float val, float threshold = 1.0) {
  return (abs(val) <= threshold) ? 0 : val;
}

bool isInRange(float heading, float targetHeading, float threshold = 1.0) {
  return abs(heading - targetHeading) <= threshold;
}

int getEncoderAverage(int leftMotor, int rightMotor) {
  /*if (abs(leftMotor) < 3) {
    return rightMotor;
  }
  if (abs(rightMotor) < 3) {
    return leftMotor;
  }*/
  return (leftMotor + rightMotor) / 2;
}

void setMotors(int left, int right) {
  motor[motorL] = left;
  motor[motorR] = right;
}

void stopMotors() {
  motor[motorL] = 0;
  motor[motorR] = 0;
}

void moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0) {
  heading = 0;

  nMotorEncoder[motorL] = 0;
  nMotorEncoder[motorR] = 0;

  wait1Msec(500);
  float ROT = (float)(getMPUrot());
//  sendArduinoCommand(1);
  wait1Msec(500);

  clearTimer(T1);

  if (power > 0) {
    while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorL], nMotorEncoder[motorR]) < deg) {
    	//getMPUHeading()
      //heading = getMPUHeading();

      //ROT = getMPUrot();
     	heading += ROT * (20/1000);

      displayCenteredBigTextLine(4, "%d", heading);

      // Checks if the gyro is outside of the specified threshold (1.0)
      if (isInRange(heading, 0, threshold)) {
        setMotors(power, power);
      }

      // If not, lower the speed of the required side of the robot to adjust back to 0
      else {
        if (heading > 0) {
          setMotors((power / cor), power);
        }
        if (heading < 0) {
          setMotors(power, (power / cor));
        }
      }
      wait1Msec(20);
    }
  }

  else {
    while (time1[T1] < time && getEncoderAverage(nMotorEncoder[motorL], nMotorEncoder[motorR]) > deg) {
      // Reads gyros rate of turn, mulitplies it by the time passed (20ms), and adds it to the current heading
      heading += (getMPUrot()) * (20 / 1000);

      // Checks if the gyro is outside of the specified threshold (1.0)
      if (isInRange(heading, 0, threshold)) {
        setMotors(power, power);
      }

      // If not, lower the speed of the required side of the robot to adjust back to 0
      else {
        if (heading > 0) {
          setMotors(power, (power / cor));
        }
        if (heading < 0) {
          setMotors((power / cor), power);
        }
      }

      wait1Msec(20);
    }
  }

  stopMotors();
}

void turn(int power, int deg, int time = 5000) {

  // 90 Degree Modifier
  /*if (abs(deg) == 90) {
    int modifier = deg *2;
    deg = modifier;
  }*/

  /*// 45 Degree Modifier
  else if (abs(deg) == 45) {
    int modifier = deg * 7/9;
    deg = modifier;
  }*/

  //heading = 0;
  heading = getMPUHeading();

  wait1Msec(500);
  int offset = getMPUrot() * -1;
  wait1Msec(500);

  clearTimer(T1);

  if (deg > 0) {
    while (time1[T1] < time && heading < deg) {
    	heading = getMPUHeading();
    	displayCenteredBigTextLine(0, "%d", heading);
    	displayCenteredBigTextLine(2, "%d", deg);
      setMotors(power, -power);
      //wait1Msec(5);
    }
    stopMotors();
		wait1Msec(10)
  }


  if (deg < 0) {
    while (time1[T1] < time && heading > deg) {
    	displayCenteredBigTextLine(4, "%d", heading);
    	displayCenteredBigTextLine(6, "%d", deg);
     	heading = getMPUHeading();
      setMotors(-power, power);
      //wait1Msec(5);
    }
    stopMotors();
    wait1Msec(10);
  }

  stopMotors();
}

void arcTurn(int power, int deg, int time = 2000) {

  /*// 90 Degree Modifier
  if (abs(deg) == 90) {
    int modifier = deg * 8/9;
    deg = modifier;
  }

  // 45 Degree Modifier
  else if (abs(deg) == 45) {
    int modifier = deg * 7/9;
    deg = modifier;
  }*/

  heading = 0;
  clearTimer(T1);
  int offset = getMPUrot() * -1;

  // Forward arcTurn
  if (power > 0) {
    if (deg > 0) {
      while (time1[T1] < time && abs(heading) < abs(deg)) {
        heading += (getMPUrot() + offset) * (20 / 1000);
        setMotors(power, 0);
        wait1Msec(20);
      }
    }

    else {
      while (time1[T1] < time && abs(heading) < abs(deg)) {
        heading += (getMPUrot() + offset) * (20 / 1000);
        setMotors(0, power);
        wait1Msec(20);
      }
    }
  }

  // Backward arcTurn (flips inequalities)
  else {
    if (deg > 0) {
      while (time1[T1] < time && abs(heading) < abs(deg)) {
        heading += (getMPUrot() + offset) * (20 / 1000);
        setMotors(power, 0);
        wait1Msec(20);
      }
    }

    else {
      while (time1[T1] < time && abs(heading) < abs(deg)) {
        heading += (getMPUrot() + offset) * (20 / 1000);
        setMotors(0, power);
        wait1Msec(20);
      }
    }
  }
  stopMotors();
}

/*void latch(bool position) {
  if (!position) {
    servo[servoL] = 225;
    servo[servoR] = 0;
  }
  if (position) {
    servo[servoL] = 150;
    servo[servoR] = 93;
  }
}*/

int getIR(){
  return HTIRS2readACDir(SENSOR_IR);
}

void moveIrUp(int speed, int IR,){
  while (getIR() < IR) {
    setMotors(speed,speed);
  }
  stopMotors();
}

void moveIrDown(int speed, int IR){
  while (getIR() > IR) {
    setMotors(speed,speed);
  }
  stopMotors();
}

void latch(bool position) {
	if (!position) {
		//servo[servoL] = 225;
		//servo[servoR] = 0;
	}
	if (position) {
		//servo[servoL] = 150;
		//servo[servoR] = 93;
	}
}

int getPos() {
	wait1Msec(175);
	if(HTIRS2readACDir(SENSOR_IR) == 3)
		return 1;
	if(HTIRS2readACDir(SENSOR_IR) == 7)
		return 2;
	if(HTIRS2readACDir(SENSOR_IR) == 0)
		return 3;
	return 0;
}
