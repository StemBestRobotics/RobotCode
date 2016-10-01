#pragma config(Motor,  port7,           funnelServo,   tmotorServoStandard, openLoop)
void funnelServoControl(){
	int btn4 = vexRT(Btn5U);
	int btn5 = vexRT(Btn5D);
	if(btn4 == 1){
		motor[funnelServo] = 131;
	}
	if(btn5 == 1){
		motor[funnelServo] = -55;
	}
}
task main()
{
while(1==1){
	funnelServoControl()
}


}
