#pragma config(Sensor, dgtl12, limit,          sensorDigitalIn)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           doorMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           funnelServo,   tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           funnelServoTwo, tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           waterServo,    tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

 /*
 Code developed by STEMBEST for the STEMATOES project. Compiled 11/6/16
 Code Team:

 Lead: Walt Weiffenbach
 Carter Rhoades
 Quin Nordmark
 Mreedul Gupta


 Controls final competition robot, which has a corn gathering arm, a seed gathering and distributing funnel with a gate, and a corn holder that has a gate to let the corn out
 in addition to being capable of driving in arcade control and in tank control, based on user input.
 */
 //Declare and initialize global variables.
 bool switched = false;
 //speedControl stores the value that controls the speed.
 float speedControl = 1;
 //toggle variables
 bool cornOne = false;
 bool cornOneCheck = false;
 bool cornTwo = false;
 bool cornTwoCheck = false;
 bool water = false;
 bool waterCheck = false;
 //This function controls the speed of the wheels, so the drivers will be able to change the speed of the robot based on te situation
 void gearShift(){
	 //Declare and initialize variables
	 int buttonUp = vexRT(Btn8L);
	 int buttonDown = vexRT(Btn8D);
	 //Says if buttonUp is pressed, motor controls are full speed
	 if (buttonUp==1){
		speedControl=1;
	 }
	 //Says if buttonDown is pressed, motor controls are half speed
	 if (buttonDown==1){
	 	speedControl=0.5;
	 }
 }
 //Function that controls the corn gathering arm
 void armMotorControl(){
 	//Declare and Initialize c2 as Vex Controller channel 1 or 2 based on drivers control style need
 	//We can change joystick controls depending on what the drivers want
 	//The arm uses two motors in order to have more torque, which was one potential design. However, the final build does not use the additional motor as it was not necesarry.
 	int c1;
 	if(switched==false){
 		c1 = vexRT[Ch2];
	}
	if(switched==true){
		c1 = vexRT[Ch1];
	}
 	//range in which the program will read from the joystick. Used to combat imperfect joysticks, in addition to being well outside the range of tank drive to avoid accidental
 	//actuation of the arm.
 	if (c1<-80||80<c1){
 		motor[armMotor] = c1;
 		} else {
 		motor[armMotor]=0;
 	}
 }
//FUNCTION that controls switches between arcade drive and tank drive
void controlSwitch(){
	 //Declaring and initializing variables
  	int btn1 = vexRT(Btn7L);
  	int btn2 = vexRT(Btn7R);
  	//Says if btn1 is pressed it goes to tank control, otherwise it goes to arcade drive
  	if(btn1==1){
  		switched=true;
  	}else if(btn2==1){
  		switched=false;
  }
}

 //Function that controls driving
 void drive(){
  if(switched==true){
  	//tank control
  	//variables that hold the joystick values.
  	int joy_y1;
  	int joy_y2;
  	//x value used to ensure there are no conflicts with the arm control.
  	int joy_x2;
  	joy_y1=vexRT[Ch3]*speedControl*-1;
  	joy_y2=vexRT[Ch2]*speedControl*-1;
  	joy_x2=vexRT[Ch1]*-1;
  	//threshold used to compensate for potentially faulty joysticks.
  	int threshold = 30;
  	//ensure no conflicts with arm control.
  	if(joy_x2>80||joy_x2<-80){
  		motor[leftMotor]=0;
  		motor[rightMotor]=0;
  	}else{
  		//tank drive control
  		if((abs(joy_y1)>threshold)){
  			motor[leftMotor]=(joy_y1/2);
  		}
  		if((abs(joy_y2)>threshold)){
  			motor[rightMotor]=(joy_y2/2);
  		}
  		if(abs(joy_y1)<threshold){
  			motor[leftMotor]=0;
  		}
  		if(abs(joy_y2)<threshold){
  			motor[rightMotor]=0;
  		}
  	}
  }else{
  	int joy_x;            // will hold the X value of the analog stick (choices below)
	 	int joy_y;            // will hold the Y value of the analog stick (choices below)
	 	int threshold = 30;		//Threshhold in which the joystick will not move, to compensate for an imperfect joystick.

	 	joy_x = vexRT[Ch4]*speedControl*-1;   //use joy_x as vex channel 4
	 	joy_y = vexRT[Ch3]*speedControl*-1;   //use joy_y as vex channel 3
	 	//The robot will move forward.
	 	if((joy_y > 40) && (abs(joy_x) < threshold))
	 	{
	 		motor[leftMotor]  = (joy_y);
	 		motor[rightMotor] = (joy_y);
	 	}
	 	//The robot will move backwards.
	 	else if(((abs(joy_x) < threshold)) && (joy_y < -40))
	 	{
	 		motor[leftMotor]  = (joy_y);
	  		motor[rightMotor] = (joy_y);
	  	}
	  	//Forwards swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE and above 40)
	 	//The y value being above 40 is present to mitigate a driver concern.
	  else if((((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y > 40)) && ((abs(joy_x) > threshold)) && (joy_y > 40))
	 	{
	 		motor[leftMotor]  = (joy_y - joy_x)/2;
	  		motor[rightMotor] = (joy_y + joy_x)/2;
	  	}
	  	// Backwards swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE and below -40)
	 	//The y value being below -40 is present to mitigate a driver concern.
	  else if((((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y < -40)) && ((abs(joy_x) > threshold)) && (joy_y < -40))
	 	{
	 		motor[leftMotor]  = (joy_y + joy_x)/2;
	  		motor[rightMotor] = (joy_y - joy_x)/2;
	  	}
	  	// Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
	 	else if((abs(joy_x) > threshold) && (abs(joy_y) < 40))
	  	{
	  		motor[leftMotor]  = joy_x;
	  		motor[rightMotor] = (-1 * joy_x);
	 	}
	 	// Standing still: (both abs(X) and abs(Y) are below the threshold)
	 	else
	 	{
	 		motor[leftMotor]  = 0;
	 		motor[rightMotor] = 0;
	 	}
  }
 }

 /*This is the function that controls the motor for the corn door
if the first button is pressed the door opens
if the second button is pressed the door closes
otherwise the motor does not move
 */
 void doorMotorControl(){
 	//Declare and initialize btn1 as a button on the vex controller, which may be changed based on driver requests.
 	int btn1 = vexRT(Btn6U);
 	int btn2 = vexRT(Btn6D);
 	if((btn1 == 1)&&(SensorValue(limit)==1)){
 		//This opens the corn door
 		motor[doorMotor] = 175;
 	}

 	else if(btn2 == 1){
 		//This part will turn the motor to close the door
 		motor[doorMotor] = -175;
 	}

	 else{
		//This part says that if the buttons are not pushed, the motor does not turn
		 motor[doorMotor] = 0;
	 }
 }

 //Function that controls the door on the seed funnel
 void funnelServoControl(){
   //Declare and initialize btn as a button on the vex controller. This may be changed based on driver requests.
 	int btn = vexRT(Btn5D);
 	if (cornOneCheck == false && btn == 1) {
 		cornOne = !cornOne;
 		cornOneCheck = true;
	}
	if (cornOneCheck == true && btn == 0) {
		cornOneCheck = false;
	}
 	if(cornOne==false){
 		motor(funnelServo)=-55;
 	}else{
 		motor(funnelServo)=87.5;
 	}
 }
 
  //Function that controls the door on the seed funnel
 void funnelServoControlTwo(){
   //Declare and initialize btn as a button on the vex controller. This may be changed based on driver requests.
 	int btn = vexRT(Btn5U);
 	if (cornTwoCheck == false && btn == 1) {
 		cornTwo = !cornTwo;
 		cornTwoCheck = true;
	}
	if (cornTwoCheck == true && btn == 0) {
		cornTwoCheck = false;
	}
 	if(cornTwo==false){
 		motor(funnelServoTwo)=-50;
 	}else{
 		motor(funnelServoTwo)=27;
 	}
 }
 
 //Function that controls the door on the seed funnel
 void waterServoControl(){
   //Declare and initialize btn as a button on the vex controller. This may be changed based on driver requests.
 	int btn = vexRT(Btn8U);
 	if (waterCheck == false && btn == 1) {
 		water = !water;
 		waterCheck = true;
	}
	if (waterCheck == true && btn == 0) {
		waterCheck = false;
	}
 	if(water==false){
 		motor(waterServo)=-175;
 	}else{
 		motor(waterServo)=175;
 	}
 }
 //Main body of program
 task main{
   motor(funnelServo)=-55;
   motor(funnelServoTwo)=-50;
   motor(waterServo)=-175;
   wait1Msec(500);
 	//Loop continuously in order to perform teleoperated tasks.
 	while(1==1){
 		drive();
 		armMotorControl();
 		doorMotorControl();
 		funnelServoControl();
		controlSwitch();
		gearShift();a
		waterServoControl ();
		funnelServoControlTwo();
 	}
 }
