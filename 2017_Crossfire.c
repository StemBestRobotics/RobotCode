#pragma config(Motor,  port2,           motorLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           motorRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           shootingMotor, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Requirements:
A basic arcade movement drive that can be switched to a tank control function that can accomidate our
drivers needs as to increase ease of use with the drivers and therefore increase the score, through
ease of driver use.

The arcade movement takes one joystick as input, or two channels, and sets the motor values if it is within
a small range of tolerence it sets it definitively (To account for design inperfection in the controler
and for slight drifing due to imperfect joystick position). These "Tolerence ranges" are a range of 30 and
they are around the contols of turning movement and directional movement

The tank movement takes two joystick inputs and uses their "Heights" as inputs to the movement motors

*/
float speedScaler = 1;//This value is multiplied by the speed as to allow for fine control over the robot if set less than one.
bool arcadeControlMethod = false;//This is switched based on driver preference, to provide advanced control
int tolerance = 30;
bool centrifugalOn = false;
/*
some drivers like tank based control (Each joysticks outputs to the motor)
and some like arcade (Generic control method where one joystick controls all movement),
this can be easily switched here as such to accomadate the specific driver's needs
*/
void arcadeDrive(){	//Function for arcade drive
	//If the joystick is in a small range from the center in both directions, the robot should be stopped
	if( abs( vexRT[Ch1] ) < tolerance && abs ( vexRT[Ch2] ) < tolerance){
		motor[motorLeft] = 0;
		motor[motorRight] = 0;
	//If the joystick is in a small vertical range, for moving forward/backward
	}else if( abs( vexRT[Ch1] ) < tolerance ){
		motor[motorLeft] = vexRT[Ch2]* speedScaler;
		motor[motorRight] = vexRT[Ch2]*-1* speedScaler;
	//If the joystick is in a small horizontal range, the robot will turn left or right
	}else if( abs( vexRT[Ch2] ) < tolerance ){
		motor[motorLeft] = vexRT[Ch1]* speedScaler;
		motor[motorRight] = vexRT[Ch1]* speedScaler;
	//If the joystick is forward, do a forward swing turn
	}else if( vexRT[Ch2] > tolerance ){
		//As the horizontal channel becomes more positive, the robot turns to the right.
		//As the horizontal channel becomes more negative, the robot turns to the left.
		//Thinking of these averages as a graph, with the horizontal channel as the input,
		//and motor output as the output, the left motor would become much higher positive number as the input becomes positive, and the right motor
		//would become a much smaller positive number as the input becomes negative.
		motor[motorLeft] = ((vexRT[Ch2]+vexRT[Ch1])* speedScaler)/2;
		motor[motorRight] = ((vexRT[Ch2]-vexRT[Ch1])* speedScaler)/-2;
	//If the joystick is negative, do a backward swing turn
	}else if( vexRT[Ch2] < -tolerance ){
		//As the horizontal channel becomes more positive, the robot turns to the left.
		//As the horizontal channel becomes more negative, the robot turns to the right.
		//Thinking of these averages as a graph, with the horizontal channel as the input,
		//and motor output as the output, the left motor would become much higher positive number as the input becomes negative, and the right motor
		//would become a much smaller positive number as the input becomes positive.
		motor[motorLeft] = ((vexRT[Ch2]+vexRT[Ch1])* speedScaler)/2;
		motor[motorRight] = ((vexRT[Ch2]-vexRT[Ch1])* speedScaler)/-2;
	}
}
//2 Joystick tank control
void tankMovement(){
	//Deadzone to correct for faulty joysticks.
	if(abs(vexRT(Ch2))<=10 && abs(vexRT(Ch3))<=10){
	motor[motorRight]=0;
	motor[motorLeft]=0;
	}else{
	//Left Joystick up/down is the left motors power
	motor[motorLeft] = vexRT[Ch3] * speedScaler;
	//Right joystick up/down is the right motors power
	motor[motorRight] = vexRT[Ch2] * -1 * speedScaler;
	}
}
void toggleArcade(){
	bool arcadeCheck = false;
	//Toggle switch. Btn7U is pressed, operating value inverts. Changes between arcade and tank drive.
	if((vexRT[Btn7U]==1)&&(arcadeCheck==false)){
			arcadeControlMethod=!arcadeControlMethod;
			arcadeCheck = true;
		}
		if((vexRT[Btn7U]==false)&&(arcadeCheck==true)){
			arcadeCheck = false;
		}
}
void toggleSpeed(){
	bool speedCheck = false;
	//Toggle switch. Btn8U is pressed, operating value inverts. Works as a gearshift, shifting between fast and slow.
	if((vexRT[Btn8U]==1)&&(speedCheck==false)){
		if(speedScaler==1){
			speedScaler=0.5;
		}else{
			speedScaler=1;
		}
		speedCheck = !speedCheck;
	}
	if((vexRT[Btn8U]==false)&&(speedCheck==true)){
		speedCheck = false;
	}
}
void drive(){
	//Toggle switch. Btn7U is pressed, operating value inverts. Changes between arcade and tank drive.
	toggleArcade();
	//Toggle switch. Btn8U is pressed, operating value inverts. Works as a gearshift, shifting between fast and slow.
	toggleSpeed();
	//Tank if driver chooses tank, arcade if driver chooses that.
	if(arcadeControlMethod==true){
		arcadearcadeDrive();
	}else{
		tankMovement();
	}
}

void shoot(){
	if((vexRT[Btn5U]==1)&&(centreCheck==false)){//This is a switch to change if the shooting motor is on, so the drivers don't have to hold down the button
		centrifugalOn= (!centrifugalOn);
		centreCheck = true;
	}
	if((vexRT[Btn5U]==false)&&(centreCheck==true)){
		centreCheck = false;
	}
	if(centrifugalOn==true){
		motor[shootingMotor] = 127;
	}else{
		motor[shootingMotor] = 0;
	}
}

//Task main is the beginning of the program
task main()
{
	//Infinitie loop causes infinite execution
	while(1==1){
		//function that controls driving
		drive();
		shoot();
	}
}
