#pragma config(Sensor, S1,     c1,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     c2,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "stack.c"

int nMotorSpeedSetting = 45, vertex = 0, count = 0, row = 0, val = 6, colorVal = 0, init = 0;
int S[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {-1, -1, -1, -1, 0},
    {1, 1, 0, 0, 0},
    {0, -1, 1, 1, 0}
};

int nr=0,ng=0, nb=0;

byte dp[25][1 << MAX_RED_PATCH];
RedSet red;
MoveArray resultMove;

void convertGraph();
bool isVisited(Point cur, int v);
byte absMove(Point robot, Point next);
byte findRedSeq(Point cur);
byte getNextScore(Point prev, Point next, int v);
int handleRed(Point cur, int v);
void getMoveArray();
void moveRobot();
void initRedSet();
void initDpTable();
void initPoint(Point &point, byte r, byte c);
void initMoveArray(MoveArray &moveArray, byte moveCount, byte *moves);
void initElement(Element &e, byte curR, byte curC, byte robR, byte robC,
byte moveCount, byte *moves, int v);

int getColor()
{
	int red[20], green[20], blue[20];
	sleep(250);

   for (int i = 0; i < 20; i++)
   {
      getColorRGB(c2, nr, ng, nb);
      red[i] = nr;
      green[i] = ng;
      blue[i] = nb;
      sleep(10);
   }
   nr = ng = nb = 0;
   for (int i = 5; i < 20; i++)
   {
      nr += red[i];
      ng += green[i];
      nb += blue[i];
   }
   nr /= 15;
   ng /= 15;
   nb /= 15;
   //display current color
   if(nr < 18) return Green;
   else if(ng < 18) return Red;
   else if(nb < 12) return Yellow;
   else return White;
}

void turnForColorSearch()
{
   setMotorSpeed(lm, 15);
   setMotorSpeed(rm, -15);
   sleep(150);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(150);
}

void storeColor()
{
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);

   colorVal = getColor();

   if (init == 0 ){
      displayBigTextLine(1, "S[%d][%d] = YELLOW", row , count);
      S[row][count] = 0;
      init++;
   }
   else if (row % 2 == 0){
      if(colorVal == 2){
         displayBigTextLine(1,"S[%d][%d] = BLUE", row, ++count);
         S[row][count] = -1;
      }
      else if (colorVal == 5){
         displayBigTextLine(1, "S[%d][%d] = RED", row, ++count);
         S[row][count] = 1;
      }
      else{
         displayBigTextLine(1, "S[%d][%d] = YELLOW", row , ++count);
         S[row][count] = 0;
      }
   }

   else if(row % 2!= 0){
      if(colorVal == 2){
         displayBigTextLine(1,"S[%d][%d] = BLUE", row, 4-(++count));
         S[row][4-count] = -1;
      }
      else if(colorVal == 5){
         displayBigTextLine(1,"S[%d][%d] = RED", row, 4-(++count));
         S[row][4-count] = 1;
      }
      else{
         displayBigTextLine(1,"S[%d][%d] = YELLOW", row, 4-(++count));
         S[row][4-count] = 0;
      }
   }
   setLEDColor(0);
   setMotorSpeed(lm, 40);
   setMotorSpeed(rm, 40);
   sleep(200);
}

void go() {
   if(getColorName(c2) == 4)
   {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
   }
   else
   {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
   }
   if(row == 1)
   {
      if(getColorName(c1) == 4 && count != 4)
      {
         vertex++;
         setMotorSpeed(lm, 12);
         setMotorSpeed(rm, 10);
         sleep(80);
      }
      else
         vertex = 0;
   }
   else if(row == 3)
   {
      if(getColorName(c1) == 4 && count != 4) vertex++;
      else vertex = 0;
   }
   else if(row == 4)
   {
      if(getColorName(c1) == 4 && count != 4) vertex++;
      else vertex = 0;
   }
   else //ROW : 0 or 2
   {
      if(getColorName(c3) == 4 && count != 4) vertex++;
      else vertex = 0;
   }

   if(vertex == 1) //Intersection : 1
   {
      if(row == 0 || row == 2 || row == 4){
         turnForColorSearch();
         sleep(150);
         setMotorSpeed(lm, 12);
         setMotorSpeed(rm, 10);
         sleep(80);
      }
      else
      {
         turnForColorSearch();
         sleep(150);
         setMotorSpeed(lm, 10);
         setMotorSpeed(rm, 12);
         sleep(80);
      }
      storeColor();
   }
}

void turnLeft()
{
	int tmp_r=0, tmp_g=0, tmp_b=0;
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(1)
   {
    getColorRGB(c2, tmp_r, tmp_g, tmp_b);
    if(tmp_b<18){break;}
    setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
    setMotorSpeed(rm, nMotorSpeedSetting * 6 /10);

   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
}

void turnRight()
{
   int tmp_r=0, tmp_g=0, tmp_b=0;
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c3) > 4)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, -nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(1)
   {
			getColorRGB(c2, tmp_r, tmp_g, tmp_b);
			if(tmp_b<18){break;}
			setMotorSpeed(lm, nMotorSpeedSetting * rotationOffset);
			setMotorSpeed(rm, -nMotorSpeedSetting * rotationOffset);
   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
}

void completeSearch()
{
   while(true)
   {
      go();
      if (count == 4)
      {
         if(row == 4) return;

         if (row % 2 == 0)
         {
            setMotorSpeed(lm,35);
            setMotorSpeed(rm,30);
            sleep(200);
            turnRight();
         }
         else
         {
            setMotorSpeed(lm,30);
            setMotorSpeed(rm,35);
            sleep(200);
            turnLeft();
         }

         row++;

         if(row%2 == 0)
         {
            while(getColorName(c1) == 6) {
               if(getColorName(c2) == 4)
               {
                  setMotorSpeed(lm, nMotorSpeedSetting - val);
                  setMotorSpeed(rm, nMotorSpeedSetting + val);
               }
               else
               {
                  setMotorSpeed(lm, nMotorSpeedSetting + val);
                  setMotorSpeed(rm, nMotorSpeedSetting - val);
               }
            }

            turnForColorSearch();
            sleep(150);
            setMotorSpeed(lm, 10);
            setMotorSpeed(rm, 10);
            sleep(80);

            count = -1; //It doesn't matter because the storeColor does ++count
            storeColor();

            setMotorSpeed(lm,30);
            setMotorSpeed(rm,35);
            sleep(200);
            turnLeft();
            setMotorSpeed(lm, -25);
            setMotorSpeed(rm, -25);
            sleep(100);
         }

         else
         {
            while(getColorName(c3) == 6) {
            	if(getColorName(c2) == 4)
               {
                  setMotorSpeed(lm, nMotorSpeedSetting - val);
                  setMotorSpeed(rm, nMotorSpeedSetting + val);
               }
               else
               {
                  setMotorSpeed(lm, nMotorSpeedSetting + val);
                  setMotorSpeed(rm, nMotorSpeedSetting - val);
               }
            }
            turnForColorSearch();
            sleep(150);
            setMotorSpeed(lm, 10);
            setMotorSpeed(rm, 10);
            sleep(80);

            count = -1; //It doesn't matter because the storeColor does ++count
            storeColor();

            setMotorSpeed(lm, 35);
            setMotorSpeed(rm, 30);
            sleep(200);
            turnRight();
            setMotorSpeed(lm, -25);
            setMotorSpeed(rm, -25);
            sleep(100);
         }
         count = 0;
         sleep(200);
      }
   }
}

void DisplayMap()
{
   char map[5][5];
   for(int i = 0; i < 5; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         if(S[i][j] == 0) map[i][j] = '+';
         else if(S[i][j] == 1) map[i][j] = 'O';
         else map[i][j] = 'X';
      }
   }
   for(int p = 0; p < 5; p++) {
      for(int q =0; q < 5; q++) {
         displayStringAt((q+1)*10, 100-(p+1)*10, "%c",map[p][q]);
      }
   }
   sleep(1000);
}

void U(){
   while(getColorName(c1) > 4 && getColorName(c3) > 4){
		if(getColorName(c2) == 4)
		{
			setMotorSpeed(lm, nMotorSpeedSetting - val);
			setMotorSpeed(rm, nMotorSpeedSetting + val);
		}
		else
		{
			setMotorSpeed(lm, nMotorSpeedSetting + val);
			setMotorSpeed(rm, nMotorSpeedSetting - val);
		}
   }
   sleep(100);
   setMotorSpeed(lm,30);
   setMotorSpeed(rm,30);
   sleep(350);
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
}

void R()
{
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c3) > 4)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, -nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4)
   {
			setMotorSpeed(lm, nMotorSpeedSetting * rotationOffset);
			setMotorSpeed(rm, -nMotorSpeedSetting * rotationOffset);
   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
	sleep(100);
  U();
}

void L(){
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4)
   {
    setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
    setMotorSpeed(rm, nMotorSpeedSetting * 6 /10);

   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
   sleep(100);
   U();
}

void D(){
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4)
   {
    setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
    setMotorSpeed(rm, nMotorSpeedSetting * 6 /10);

   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
   sleep(100);
   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
      setMotorSpeed(rm, nMotorSpeedSetting * rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4)
   {
    setMotorSpeed(lm, -nMotorSpeedSetting * rotationOffset);
    setMotorSpeed(rm, nMotorSpeedSetting * 6 /10);

   }
   sleep(100);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
   sleep(200);
   count = 0;
   U();
}

void convertGraph()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
            if (S[i][j] == 0) S[i][j] = -1;
            else if (S[i][j] == 1) S[i][j] = 4;
            else if (S[i][j] == -1) S[i][j] = -4;
            else S[i][j] = Error;
		}
}

void initDpTable()
{
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < (1 << MAX_RED_PATCH); j++)
			dp[i][j] = MIN;
	dp[24][0] = 0;
}

byte absMove(Point robot, Point next)
{
	if (robot.r == 1 && robot.c == 0)
	{
		if (next.r == -1 && next.c == 0) return Down;
		if (next.r == 1 && next.c == 0) return Up;
		if (next.r == 0 && next.c == -1) return Right;
		if (next.r == 0 && next.c == 1) return Left;
	}
	if (robot.r == -1 && robot.c == 0)
	{
		if (next.r == -1 && next.c == 0) return Up;
		if (next.r == 1 && next.c == 0) return Down;
		if (next.r == 0 && next.c == -1) return Left;
		if (next.r == 0 && next.c == 1) return Right;
	}
	if (robot.r == 0 && robot.c == 1)
	{
		if (next.r == -1 && next.c == 0) return Left;
		if (next.r == 1 && next.c == 0) return Right;
		if (next.r == 0 && next.c == -1) return Down;
		if (next.r == 0 && next.c == 1) return Up;
	}
	if (robot.r == 0 && robot.c == -1)
	{
		if (next.r == -1 && next.c == 0) return Right;
		if (next.r == 1 && next.c == 0) return Left;
		if (next.r == 0 && next.c == -1) return Up;
		if (next.r == 0 && next.c == 1) return Down;
	}
	return -1; // error
}

byte findRedSeq(Point cur)
{
	for (byte i = 0; i < red.count; i++)
	{
		if ((red.redArray[i].r == cur.r) && (red.redArray[i].c == cur.c))
			return i;
	}
	return -1; // error
}

bool isVisited(Point cur, int v)
{
	if (((1 << findRedSeq(cur)) & v) > 0) return true;
	return false;
}

byte getNextScore(Point prev, Point next, int v)
{
	if ((S[next.r][next.c] == 4) && isVisited(next, v))
		return dp[5 * prev.r + prev.c][v] - 4;
	return dp[5 * prev.r + prev.c][v] + S[next.r][next.c];
}

int handleRed(Point cur, int v)
{
	if ((S[cur.r][cur.c] != 4) || isVisited(cur, v))
		return v;
	return ((1 << findRedSeq(cur)) | v);
}

void initRedSet()
{
	red.count = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (S[i][j] == 4)
			{
				red.redArray[red.count].r = i;
				red.redArray[red.count].c = j;
				red.count++;
			}
		}
	}
}

void initPoint(Point &point, byte r, byte c)
{
	point.r = r;
	point.c = c;
}

void initMoveArray(MoveArray &moveArray, byte moveCount, byte *moves)
{
	moveArray.moveCount = moveCount;
	for (int i = 0; i < moveCount; i++)
		moveArray.moves[i] = moves[i];
}


void initElement(Element &e, byte curR, byte curC, byte robR, byte robC,
byte moveCount, byte *moves, int v)
{
	e.cur.r = curR;
	e.cur.c = curC;
	e.robot.r = robR;
	e.robot.c = robC;
	e.v = v;
	e.moveArray.moveCount = moveCount;
	for (int i = 0; i < moveCount; i++)
		e.moveArray.moves[i] = moves[i];
}

void getMoveArray()
{
	byte nextScore;
	short maxScore = MIN;
	int nv;
	Point cur, robotDir, dir, next;
	MoveArray curMove, nextMove;
	Element e;
	Stack s;
	byte directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	initRedSet();
	initStack(&s);
	initElement(e, 4, 4, 0, -1, 0, curMove.moves, 0);
	push(&s, e);

	while (!isEmpty(&s))
	{
		pop(&s, e);
		initPoint(cur, e.cur.r, e.cur.c);
		initPoint(robotDir, e.robot.r, e.robot.c);
		initMoveArray(curMove, e.moveArray.moveCount, e.moveArray.moves);

		for (int i = 0; i < 4; i++)
		{
			initPoint(dir, directions[i][0], directions[i][1]);
			initPoint(next, cur.r + dir.r, cur.c + dir.c);
			if (next.r < 0 || next.r >= 5 || next.c < 0 || next.c >= 5) continue;
			nextScore = getNextScore(cur, next, e.v);
			nv = handleRed(next, e.v);
			if (dp[5 * next.r + next.c][nv] < nextScore)
			{
				initMoveArray(nextMove, curMove.moveCount, curMove.moves);
				nextMove.moves[nextMove.moveCount++] = absMove(robotDir, dir);
				dp[5 * next.r + next.c][nv] = nextScore;
				if (next.r == 0 && next.c == 0 && dp[0][nv] > maxScore)
				{
					maxScore = dp[0][nv];
					initMoveArray(resultMove, nextMove.moveCount, nextMove.moves);
				}
				if (nextMove.moveCount < MAX_MOVE_COUNT)
				{
					initElement(e, next.r, next.c, dir.r, dir.c, nextMove.moveCount, nextMove.moves, nv);
					push(&s, e);
				}
			}
		}
	}
}

void moveRobot()
{
	for (int i = 0; i < resultMove.moveCount; i++)
	{
		if (resultMove.moves[i] == Up) U();
		else if (resultMove.moves[i] == Down) D();
		else if (resultMove.moves[i] == Left) L();
		else if (resultMove.moves[i] == Right) R();
		setMotorSpeed(lm, 0);
		setMotorSpeed(rm, 0);
		sleep(1000);
	}
}

void printMove()
{
	char converts[5] = {0, 'U', 'D', 'L', 'R'};
	for (int i = 0; i < resultMove.moveCount / 2; i++)
		displayStringAt(i * 10, 100, "%c ",  converts[resultMove.moves[i]]);
	for (int i = resultMove.moveCount / 2; i < resultMove.moveCount; i++)
		displayStringAt((i - resultMove.moveCount / 2) * 10, 90, "%c ",  converts[resultMove.moves[i]]);
}

void printMaxScore()
{
	byte mx = MIN;
	for (int i = 0; i < 1 << MAX_RED_PATCH; i++)
		if (mx < dp[0][i]) mx = dp[0][i];
	displayBigTextLine(1, "maxCount: %d", mx);
}

task main()
{

	/*resultMove.moves[0] = Up;
	resultMove.moves[1] = Up;
	resultMove.moves[2] = Right;
	resultMove.moves[3] = Left;
	resultMove.moves[4] = Up;
	resultMove.moves[5] = Right;
	resultMove.moves[6] = Up;
	resultMove.moves[7] = Right;
	resultMove.moves[8] = Up;
	resultMove.moves[9] = Left;
	resultMove.moves[10] = Left;
	resultMove.moves[11] = Up;
	resultMove.moveCount = 12;*/
	completeSearch();
	setMotorSpeed(lm,30);
	setMotorSpeed(rm,30);
	sleep(350);
	turnLeft();
	turnLeft();

	sleep(2000);
	eraseDisplay();
	DisplayMap();
	sleep(1000);
	eraseDisplay();
	convertGraph();
	initDpTable();
	getMoveArray();
	printMove();
	moveRobot();
	printMaxScore();
	sleep(10000);
}