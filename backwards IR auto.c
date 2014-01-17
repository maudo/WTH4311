#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     Ultra,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     driveRight,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     driveLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     armRight,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armLeft,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     plow,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     twirler,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    cube,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    test,                 tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "drivers/hitechnic-gyro.h"

void turn(int angle, short speed)  // Steven Mostovoy
{
	if (angle > 0)
		angle += 65;
	else
	  angle -= 65;
	if (angle < 0)
	{
		angle *= -1;
		speed *= -1;
	}
	wait1Msec(200);

	HTGYROstartCal(S2);

	wait1Msec(200);
	int gyro[3] = {0,0,0};
	int gyroMid[3] = {0,0,0};
	int gyroFinal[4] = {0,0,0,0};
	motor[driveLeft] = speed;
	motor[driveRight] = -speed;
	int integral = 0;
	while (true)
	{
		for (int i = 2; i > 0; --i)
			gyro[i] = gyro[i-1];
		gyro[0] = HTGYROreadRot(S3);

		float mu = 10.0/11.0;

		gyroMid[0] = gyro[0];
		for (int i = 1; i < 3; ++i)
			gyroFinal[i] = mu * (gyro[i] - gyroMid[i-1]) + gyroMid[i-1];

		for (int i = 3; i > 0; --i)
			gyroFinal[i] = gyroMid[i-1];
		gyroFinal[0] = gyroMid[1];

		integral += (gyroFinal[0] + gyroFinal[1]*2 + gyroFinal[2]*2 + gyroFinal[3])/6;

		//writeDebugStreamLine("%d", integral);
		if (abs(integral * 0.0604) > angle) break;
		wait1Msec(10);
	}
	motor[driveLeft] = 0;
	motor[driveRight] = 0;
}

task main()
{
	waitForStart();
	motor[plow] = 75;
	motor[armLeft] = -100;
	motor[armRight] = -100;
	wait1Msec(100);
	motor[plow] = 0;
	motor[armLeft] = 0;
	motor[armRight] = 0;
	bool nope = false;

	nMotorEncoder[driveLeft] = 0;
	//time1[T1] = 0;

	while(SensorValue[IR] != 5)
	{
		//writeDebugStreamLine("%d", SensorValue[IR]);
		writeDebugStreamLine("%d", nMotorEncoder[driveLeft]);
		//if(time1[T1] > 6000)
			//break;
		//else
		//{

		if(nMotorEncoder[driveLeft] < -5300)
		{
			nope = true;
			break;
		}

		motor[driveLeft] = -100;
		motor[driveRight] = -100;
		//}
	}

	//time1[T1] = 0;
	int temp = nMotorEncoder[driveLeft];

	if(!nope)
	{
		while(nMotorEncoder[driveLeft] > (temp + -200))
		{
			motor[driveLeft] = -100;
			motor[driveRight] = -100;
		}

		motor[driveLeft] = 0;
		motor[driveRight] = 0;
		wait1Msec(500);
	}

	servo[cube] = 0;
	wait1Msec(1000);
	servo[cube] = 125;
	wait1Msec(1000);

	nMotorEncoder[driveLeft] = 0;

	while(SensorValue[Ultra] > 25)
	{
		//riteDebugStreamLine("%d", SensorValue[Ultra]);
		motor[driveLeft] = -100;
		motor[driveRight] = -100;
	}
	motor[driveLeft] = 0;
	motor[driveRight] = 0;

	/*if(!nope)
	{
		while(nMotorEncoder[driveLeft] < (-temp + 300))
		{
			motor[driveLeft] = 100;
			motor[driveRight] = 100;
		}

		motor[driveLeft] = 0;
		motor[driveRight] = 0;
		wait1Msec(750);
	}
	else
	{
		while(nMotorEncoder[driveLeft] < (5300+150))
		{
			motor[driveLeft] = 100;
			motor[driveRight] = 100;
		}

		motor[driveLeft] = 0;
		motor[driveRight] = 0;
		wait1Msec(750);
	}*/



	turn(-90,75);

	nMotorEncoder[driveLeft] = 0;
	/*while(nMotorEncoder[driveLeft] > -3900)
	{
		motor[driveLeft] = -100;
		motor[driveRight] = -100;
	}

	motor[driveLeft] = 0;
	motor[driveRight] = 0;
	wait1Msec(750);*/

	motor[driveLeft] = -100;
	motor[driveRight] = -100;
	wait1Msec(1250);

	motor[driveLeft] = 0;
	motor[driveRight] = 0;
	wait1Msec(500);

	turn(55,75);

	/*nMotorEncoder[driveLeft] = 0;

	while(nMotorEncoder[driveLeft] > -3000)
	{
		motor[driveLeft] = -100;
		motor[driveRight] = -100;
	}*/

	motor[driveLeft] = 0;
	motor[driveRight] = 0;
	wait1Msec(250);

	motor[driveLeft] = -100;
	motor[driveRight] = -100;
	wait1Msec(1500);

	motor[driveLeft] = 0;
	motor[driveRight] = 0;
}
