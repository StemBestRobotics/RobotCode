 #pragma config(Motor,  port3,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
 #pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port4,           armMotor,      tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port5,           armMotor2,  tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port6,           doorServo,     tmotorServoStandard, openLoop)
 #pragma config(Motor,  port7,           funnelServo,     tmotorServoStandard, openLoop)
 //*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
 /*
 Code developed by STEMBEST for the STEMATOES project. Compiled 10/14/16
 Code Team:

 Lead: Walt Weiffenbach
 Carter Rhoades
 Quin Nordmark
 Mreedul Gupta


 Controls final competition robot, which has a corn gathering arm, a seed gathering and distributing funnel with a gate, and a corn holder that has a gate to let the corn out
 in addition to being capable of driving in arcade control and in tank control, based on user input.
 */
 //Declare and initiallize global variables.
 bool switched = false;
 //Function that controls the corn gathering arm
 void armMotorControl(){
 	//Declare and Initialize c2 as Vex Controller channel 2
 	//We can change joystick controls depending on what the drivers want
 	//The arm uses two motors in order to have more torque, which was one potential design. However, the final build does not use the additional motor as it was not necesarry.
 	int c1;
 	if(switched==false){
 		c1 = vexRT[Ch2];
	}
	if(switched==true){
		c1 = vexRT[Ch1];
	}
 	//range in which the program will read from the joystick. Used to combat imperfect joysticks, in addition to being well outside the range of tank drive toavoid accidental
 	//actuation of the arm.
 	if (c1<-80||80<c1){
 		motor[armMotor] = c1;
 		motor[armMotor2] = c1;
 		} else {
 		motor[armMotor2]=0;
 		motor[armMotor]=0;
 	}
 }

 //Function that controls driving
 void drive(){
  int btn1 = vexRT(Btn7L);
  int btn2 = vexRT(Btn7R);
  if(btn1==1){
  	pressed=true;
  }else if(btn2==1){
  	pressed=false;
  }
  if(pressed==true){
  	//tank control
  	//variables that hold the joystick values.
  	int joy_y1;
  	int joy_y2;
  	//x value used to ensure there are no conflicts with the arm control.
  	int joy_x2;
  	joy_y1=vexRT[Ch3]*-1;
  	joy_y2=vexRT[Ch2]*-1;
  	joy_x2=vexRT[Ch1]*-1;
  	//threshold used to compensate for potentially faulty joysticks.
  	int threshold = 30;
  	//ensure no conflicts with arm control.
  	if(joy_x2>80||joy_x2<-80){
  		motor[leftMotor]=0;
  		motor[rightMotor]=0;
  	}
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
  }else{
  	int joy_x;            // will hold the X value of the analog stick (choices below)
	 	int joy_y;            // will hold the Y value of the analog stick (choices below)
	 	int threshold = 30;		//Threshhold in which the joystick will not move, to compensate for an imperfect joystick.

	 	joy_x = vexRT[Ch4]*-1;   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
	 	joy_y = vexRT[Ch3]*-1;   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

	 	// Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE and above 40)
	 	//The y value being above 40 is present to mitigate a driver concern.
	 	if((joy_y > 40) && (abs(joy_x) < threshold))
	 	{
	 		motor[leftMotor]  = (joy_y);
	 		motor[rightMotor] = (joy_y);
	 	}
	 	// Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE and below -40)
	 	//The ya value being below -40 is present to mitigate a driver concern.
	 	else if(((abs(joy_x) < threshold)) && (joy_y < -40))
	 	{
	 		motor[leftMotor]  = (joy_y);
	  		motor[rightMotor] = (joy_y);
	  	}
	  else if((((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y > 40)) && ((abs(joy_x) > threshold)) && (joy_y > 40))
	 	{
	 		motor[leftMotor]  = (joy_y - joy_x)/2;
	  		motor[rightMotor] = (joy_y + joy_x)/2;
	  	}
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

 //This function controls the servo for the corn door
 void doorServoControl(){
 	//Declare and initialize btn1 as a button on the vex controller, which may be changed based on driver requests.
 	int btn1 = vexRT(Btn5U);
 	int btn2 = vexRT(Btn5D);
 	if(btn1 == 1){
 		//turn the servo to its maximum range.
 		motor[doorServo] = 175;
 	}
 	if(btn2 == 1){
 		//turn the servo to its minimum range.
 		motor[doorServo] = -175;
 	}
 }

 //Function that controls the door on the seed funnel
 void funnelServoControl(){
 	//declare and initialize btn4 as a button on the vex controller. This may be changed based on driver requests.
 	int btn4 = vexRT(Btn6U);
 	//declare and initialize btn5 as a button on the vex controller. This may be changed based on driver requests.
 	int btn5 = vexRT(Btn6D);
 	if(btn4 == 1){
 		//turn funnel servo to 90 degrees.
 		motor[funnelServo] = 87.5;
 	}
 	if(btn5 == 1){
 		//turn funnel servo to 0 degrees.
 		motor[funnelServo] = -175;
 	}
 }

 //Main body of program
 task main{
 	//Loop continuously in order to perform teleoperated tasks.
 	while(1==1){
 		drive();
 		armMotorControl();
 		doorServoControl();
 		funnelServoControl();
 	}
 }
