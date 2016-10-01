 #pragma config(Motor,  port4,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
 #pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port6,           armMotor,      tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port7,           armMotor2,  tmotorVex393_MC29, openLoop)
 #pragma config(Motor,  port8,           doorServo,     tmotorServoStandard, openLoop)
 #pragma config(Motor,  port9,           funnelServo,     tmotorServoStandard, openLoop)
 //*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//




 /void arcadeDrive(){
 	int joy_x;            // will hold the X value of the analog stick (choices below)
 	int joy_y;            // will hold the Y value of the analog stick (choices below)
 	int threshold = 20;		//Threshhold in which the joystick will not move, to compensate for an imperfect joystick.
 
 	joy_x = vexRT[Ch4];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
 	joy_y = vexRT[Ch3];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.
 
 	// Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE and above 40)
 	//The y value being above 40 is present to mitigate a driver concern.
 	if(((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y > 40))
 	{
 		motor[leftMotor]  = (joy_y + joy_x)/2;
 		motor[rightMotor] = (joy_y - joy_x)/2;
 	}
 	// Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE and below -40)
 	//The ya value being below -40 is present to mitigate a driver concern.
 	else if(((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y < -40))
 	{
 		motor[leftMotor]  = (joy_y - joy_x)/2;
  		motor[rightMotor] = (joy_y + joy_x)/2;
  	}
  	// Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
 -	else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
 +	else if((abs(joy_x) > threshold) && (abs(joy_y) < 40))
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





 //Main body of program
 task main{
 	//Loop continuously in order to perform teleoperated tasks.
 	while(1==1){
 		arcadeDrive();

 	}
 }
