#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightArm,      tmotorVex393_MC29, openLoop, reversed)
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
task main()
{
while(1==1) {
	armMotorControl();
}


}
