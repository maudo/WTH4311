#pragma config(Sensor, S3,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     Ultra,          sensorNone)
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
	turn(-30,75);
}
