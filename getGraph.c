#pragma config(Sensor, S1,     cs1,            sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     cs2,            sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     cs3,            sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)

#define White 0
#define Yellow 1
#define Red 2
#define Green 3

// adjustable values
int nMotorSpeedSetting = 20;
// non-adjustable values
int val = 0, leftV = 0, rightV = 0, centerV = 0, row = 0, col = 0, maxRow = 0, maxCol = 0, r, g, b;
bool turnFlag = false, finishFlag = true;
int red[50], green[50], blue[50];

// A graph of board (yellow: 1, red: 2, blue: 3)
int graph[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1}
};

void setSpeed(int ls, int rs)
{
	setMotorSpeed(lm, ls);
	setMotorSpeed(rm, rs);
}

void stopRobot()
{
	setSpeed(0, 0);
	sleep(100);
}

// sorting array arr by ascending
void bubbleSort(int* arr)
{
	int i, j, tmp;
	for (i = 0; i < 50 - 1; i++)
		for (j = 0; j < 50 - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j + 1];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
}

// get the color of the current location
int getColor()
{

	for (int i = 0; i < 50; i++)
	{
		getColorRGB(cs2, r, g, b);
		red[i] = r;
		green[i] = g;
		blue[i] = b;
	}
	r = g = b = 0;
	bubbleSort(red); bubbleSort(green); bubbleSort(blue);
	for (int i = 10; i < 40; i++)
	{
		r += red[i];
		g += green[i];
		b += blue[i];
	}
	r /= 30;
	g /= 30;
	b /= 30;

	//display current color
	if(r < 12)
	{
		displayTextLine(2, "Green");
		return Green;
	}
	else if(g < 12)
	{
		displayTextLine(2, "Red");
		return Red;
	}
	else if(b < 12)
	{
		displayTextLine(2, "Yellow");
		return Yellow;
	}
	else
	{
		displayTextLine(2, "White");
		return White;
	}
}

int getReflected(int robot)
{
	int bound[4] = {0, 20, 0, 30};
	for (int i = 0; i < 50; i++)
	{
		if (robot == 1) getColorRGB(cs1, r, g, b);
		if (robot == 3) getColorRGB(cs3, r, g, b);
		blue[i] = b;
	}
	b = 0;
	bubbleSort(blue);
	for (int i = 10; i < 40; i++)
		b += blue[i];
	b /= 30;

	//display current color
	if(b < bound[robot])
	{
		displayTextLine(robot, "Yellow");
		return Yellow;
	}
	else
	{
		displayTextLine(robot, "White");
		return White;
	}
}

// d:1 -> right, 2 -> left
bool checkEnd(int d)
{
	stopRobot();
	if ((d == 1 && getReflected(3)) || (d == 0 && getReflected(1)))
	{
		setSpeed(nMotorSpeedSetting, nMotorSpeedSetting);
		return true;
	}
	setSpeed(nMotorSpeedSetting, nMotorSpeedSetting);
	return false;
}

void go()
{
	val = 2;
	if (getColor() == Yellow) setSpeed(nMotorSpeedSetting - val, nMotorSpeedSetting + val);
	else setSpeed(nMotorSpeedSetting + val, nMotorSpeedSetting - val);

	if (getReflected(1) == Yellow || getReflected(3) == Yellow)
	{
		stopRobot();
		setSpeed(nMotorSpeedSetting - 5, nMotorSpeedSetting - 5);
		sleep(140);

		if (getReflected(1) == Yellow) leftV++;
		else leftV = 0;

		if (getReflected(3) == Yellow) rightV++;
		else rightV = 0;

		if (leftV == 1 || rightV == 1)
		{
			col++;
			//attachPatch(row, col++);
		}
	}
	if (getColor() == White) centerV++;
	else centerV = 0;

	if (centerV > 450) turnFlag = true;
}

void attachPatch(int r, int c)
{
	stopRobot();
	if (r % 2 == 0) graph[r][c] = getColor();
	else graph[r][maxCol - c - 1] = getColor();
	setSpeed(nMotorSpeedSetting, nMotorSpeedSetting);
}

// turn to left
void turnLeft()
{
	while (getReflected(1) == White)
	{
		setSpeed(-nMotorSpeedSetting * rotationOffset, nMotorSpeedSetting * rotationOffset);
		sleep(10);
	}

	while (getColor() == White)
	{
		setSpeed(-nMotorSpeedSetting * rotationOffset, nMotorSpeedSetting * rotationOffset);
		sleep(5);
	}
	stopRobot();
}

// turn to right
void turnRight()
{
	while (getReflected(3) == White)
	{
		setSpeed(nMotorSpeedSetting * rotationOffset, -nMotorSpeedSetting * rotationOffset);
		sleep(10);
	}

	while (getColor() == White)
	{
		setSpeed(nMotorSpeedSetting * rotationOffset, -nMotorSpeedSetting * rotationOffset);
		sleep(5);
	}
	stopRobot();
}

void getGraph()
{
	while (finishFlag)
	{
		go();
		if (turnFlag)
		{
			maxCol = col;
			row++;
			turnFlag = false;
			if (checkEnd(row % 2))
			{
				maxRow = row;
				break;
			}
			for (int i = 0; i < 2; i++)
			{
				if (row % 2 == 0)
				{
					turnLeft();
					if (i == 0) while (getReflected(1) == White) go();
				}
				else
				{
					turnRight();
					if (i == 0) while (getReflected(3) == White) go();
				}
			}
		}
		col = 0;
	}
}

task main()
{
	getGraph();
	sleep(5000);
}
