#pragma config(Motor,  port2,           leftWheel,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           rightWheel,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightArm,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           doorServo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           funnelServo,   tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void armMotorControl(){

	//Declare and Initialize Ch2i as Vex Controller channel 2, which
	//We can change joystick controls depending on what the driver wants
	int Ch2i = vexRT[Ch2];
	if (Ch2i<-30||30<Ch2i){
		motor[leftArm] = Ch2i;

		motor[rightArm] = Ch2i;
		} else {
		motor[leftArm]=0;
		motor[rightArm]=0;
	}
}

void arcadeDrive(){

	int joy_x;            // will hold the X value of the analog stick (choices below)
	int joy_y;            // will hold the Y value of the analog stick (choices below)
	int threshold = 10;

	joy_x = vexRT[Ch3];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
	joy_y = vexRT[Ch4];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

	// Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
	if(((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y > 0))
	{
		motor[rightWheel]  = (joy_y + joy_x)/2;
		motor[leftWheel] = (joy_y - joy_x)/2;
	}
	// Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
	else if(((abs(joy_x) > threshold) || (abs(joy_y) > threshold)) && (joy_y < 0))
	{
		motor[rightWheel]  = (joy_y - joy_x)/2;
		motor[leftWheel] = (joy_y + joy_x)/2;
	}
	// Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
	else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
	{
		motor[rightWheel]  = joy_x;
		motor[leftWheel] = (-1 * joy_x);
	}
	// Standing still: (both abs(X) and abs(Y) are below the threshold)
	else
	{
		motor[rightWheel]  = 0;
		motor[leftWheel] = 0;
	}
}


void funnelServoControl(){
	int btn4 = vexRT(Btn5U);
	int btn5 = vexRT(Btn5D);
	if(btn4 == 1){
		motor[funnelServo] = 127;
	}
	if(btn5 == 1){
		motor[funnelServo] = 30;
	}
}

void doorServoControl(){
	int btn1 = vexRT(Btn6U);
	int btn2 = vexRT(Btn6D);
	if(btn1 == 1){
		motor[doorServo] = 360;
	}
	if(btn2 == 1){
		motor[doorServo] = -50;
	}
}

task main{

	while(1==1){
		armMotorControl();
		arcadeDrive();
		funnelServoControl();
		doorServoControl();
	}
}
