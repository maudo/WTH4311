#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     plow,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     twirler,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    auto,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	int leftSpeed = 0;
	int rightSpeed = 0;
	int threshold = 20;

	//servo[wrist] = 90;
	//wait1Msec(1000);

	while(true)
	{
		getJoystickSettings(joystick);

		leftSpeed = joystick.joy1_y1;
		rightSpeed = joystick.joy1_y2;

		if(abs(leftSpeed) > threshold)
			motor[driveLeft] = leftSpeed;
		else
			motor[driveLeft] = 0;

		if(abs(rightSpeed) > threshold)
			motor[driveRight] = rightSpeed;
		else
			motor[driveRight] = 0;

		if(joy2Btn(7))
			motor[armLeft] = 100;
		else if(joy2Btn(5))
			motor[armLeft] = -100;
		else
			motor[armLeft] = 0;

		if(joy2Btn(8))
			motor[armRight] = 100;
		else if(joy2Btn(6))
			motor[armRight] = -100;
		else
			motor[armRight] = 0;

		if(joy1Btn(6))
			motor[twirler] = 100;
		else if(joy1Btn(5))
			motor[twirler] = -100;
		else
			motor[twirler] = 0;

		if (abs(joystick.joy2_y2) > threshold) 				// > 20
			 motor[plow] = joystick.joy2_y2;
		/*else if (joystick.joy2_y2 < -threshold)		// < -20
		{
					motor[plow] = joystick.joy2_y2;
					motor[plow] = 100;
					wait1Msec(50);
		}*/
		else																			//if motor value is at -20 between 20
				motor[plow] = 0;


		if(joy2Btn(9))
			servo[auto]-=5;
		else if(joy2Btn(10))
			servo[auto]+=5;

		if(joystick.joy2_y1 > threshold)
			servo[wrist] += 5;
		else if(joystick.joy2_y1 < -threshold)
			servo[wrist] -= 5;
		else if(joy2Btn(1))
			servo[wrist] = 190 	; //200 starting position
		//servo[wrist] += 5;
		else if(joy2Btn(4))
			servo[wrist] = 255; // pickup position
		//servo[wrist] -= 5;
		else if(joy2Btn(3))
			servo[wrist] = 0; //drop position

		wait1Msec(20);
	}
}
