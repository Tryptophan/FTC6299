# FTC Team QUADX 6299 Source Code

[See our cheat sheet on how to use GitHub.](https://docs.google.com/file/d/0B5eawMJjTXR9Y0NiX0NheXZ1dTA/edit)

<h2><strong>"libs.h"</strong></h2>

<code>valInRange(float val, float threshold = 1.0)</code>
* Tests if the the absolute value of the val parameter is less than the threshold and returns a boolean
* Threshold parameter default is 1.0

<code>getEncoderAverage(int leftMotor, int rightMotor)</code>
* Averages out the two paramters entered and returns a integer
* Failsafe if either left-side motor encoder or right-side motor encoder dies
 
<code>setMotors(int left, int right)</code>
* Sets the left-side drive motors to the first parameter entered and the right-side drive motors to the second parameter
 
<code>stopMotors()</code>
* Stops all of the drive motors

<code>moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0)</code>
* Moves the robot forward or backward the amount of degrees entered in the deg parameter at the power of the power parameter
* In order for the robot to move backward make the power and deg parameters negative
* The robot will correct its direction by changing motor speeds if the robot's drift in degrees gets out of the threshold parameter
* If the method runs for more than the time paratemeter the method will stop as a failsafe in case the encoders fail

<code>turn(int power, int deg, int time = 5000)</code>
* The robot will turn for the degrees given in the deg parameter on a point at the power of the power parameter
* If the method runs for more than the time parameter the method will stop for a failsafe if the gyro fails
 
<code>arcTurn(int power, int deg, int time = 2000)</code>
* Turns on one stopped motor for the degrees given in the deg parameter at the power of the power parameter
* If the method runs for more than the time parameter the method will stop for a failsafe in the gyro fails

<code>getIR()</code>
* Returns IR value
 
<code>moveIrUp(int speed, int IR)</code>
* Moves the robot until the IR value becomes greater then the IR parameter

<code>moveIrDown(int speed, int IR)</code>
* Moves the robot until the IR value becomes less then the IR parameter

<code>sendArduinoCommand(unsigned char command)</code>
* Send a command to the Arduino Pro Mini atMega via the hitechnic SuperPro
* <b>Addition of the "HTSPBWriteStrobe" to the hitechnic-superpro.h file is necessary for this to work</b>
* Commands available to send to the Arduino: 
<ol>
 <ol>
  <li>Command = 1: Tell the arduino to blink its LED (mostly for debug)</li>
  <li>Command = 2: Tell the Arduino to send the first 8 bits of the heading from the MPU</li>
  <li>Command = 3: Tell the Arduino to send the second 8 bits of the heading from the MPU</li>
  </ol>
</ol>

<code>getMPUHeading()</code>
* Reads and returns the current heading from the MPU6050


