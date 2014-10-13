# FTC Team QUADX 6299 Source Code

[See our cheat sheet on how to use GitHub.](https://docs.google.com/file/d/0B5eawMJjTXR9Y0NiX0NheXZ1dTA/edit)

<code><h3>valInRange(float val, float threshold = 1.0)</h3></code>
* Tests if the the absolute value of the val parameter is less than the threshold and returns a boolean
* Threshold parameter default is 1.0

<code><h3>getEncoderAverage(int leftMotor, int rightMotor)</h3></code>
* Averages out the two paramters entered and returns a integer
* Failsafe if either left-side motor encoder or right-side motor encoder dies
 
<code><h3>setMotors(int left, int right)</h3></code>
* Sets the left-side drive motors to the first parameter entered and the right-side drive motors to the second parameter
 
<code><h3>stopMotors()</h3></code>
* Stops all of the drive motors

<code><h3>moveTo(int power, int deg, float threshold = 2.0, long time = 5000, float cor = 4.0)</h3></code>
* Moves the robot forward or backward the amount of degrees entered in the deg parameter at the power of the power parameter
* In order for the robot to move backward make the power and deg parameters negative
* The robot will correct its direction by changing motor speeds if the robots drift in degrees gets out of the threshold parameter
* If the method runs for more than the time paratemeter the method will stop for a failsafe if the encoders fail

<code><h3>turn(int power, int deg, int time = 5000)</h3></code>
* The robot will turn for the degrees given in the deg parameter on a point at the power of the power parameter
* <b>The turn method only turns 45° and 90° currently<b>
* If the method runs for more than the time parameter the method will stop for a failsafe if the gyro failsafe
 
<code><h3>arcTurn(int power, int deg, int time = 2000)</h3></code>
* Turns on one stopped motor for the degrees given in the deg parameter at the power of the power parameter
* <b>The turn method only turns 45° and 90° currently<b>
* If the method runs for more than the time parameter the method will stop for a failsafe in the gyro failsafe

<code><h3>getIR()</h3></code>
* Returns IR value
 
<code><h3>moveIrUp(int speed, int IR)</h3></code>
* Moves the robot until the IR value becomes greater then the IR parameter

<code><h3>moveIrDown(int speed, int IR)</h3></code>
* Moves the robot until the IR value becomes less then the IR parameter
