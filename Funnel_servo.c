#pragma config(Motor,  port6,           doorServo,     tmotorServoStandard, openLoop)
//Function that controls the seed funnel servo
void doorServoControl(){
	int btn1 = vexRT(Btn6U);
	int btn2 = vexRT(Btn6D);
	if(btn1 == 1){
		motor[doorServo] = 360;
	}
	if(btn2 == 1){
		motor[doorServo] = -360;
	}
}
task main(){
	while(1==1) {
		doorServoControl();



	}
}
