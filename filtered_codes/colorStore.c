void setSpeed(float leftSpeed, float rightSpeed);
int getColor();
void turnForColorSearch();
void storeColor();
void go();
void turnLeft();
void turnRight();
void completeSearch();
void DisplayMap();
void leftTask();
void rightTask();
void goUp();
void goDown();
void goLeft();
void goRight();
void moveRobot();

void setSpeed(float leftSpeed, float rightSpeed)
{
   setMotorSpeed(lm, (int) leftSpeed);
   setMotorSpeed(rm, (int) rightSpeed);
}

int getColor()
{
   int nr = 0, ng = 0, nb = 0;
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
   nr /= 15; ng /= 15; nb /= 15;
   //display current color
   if(nr < 18) return Green;
   else if(ng < 18) return Red;
   else if(nb < 12) return Yellow;
   else return White;
}

void turnForColorSearch()
{
   setSpeed(15, -15);
   sleep(150);
   setSpeed(0, 0);
   sleep(150);
}

void storeColor()
{
   setSpeed(0, 0);

   int colorVal = getColor();

   if (g_init == 0 ){
      displayBigTextLine(1, "S[%d][%d] = YELLOW", g_row , g_count);
      S[g_row][g_count] = 0;
      g_init++;
   }
   else if (g_row % 2 == 0){
      if(colorVal == 2){
         setLEDColor(1);
         displayBigTextLine(1,"S[%d][%d] = BLUE", g_row, ++g_count);
         S[g_row][g_count] = -1;
      }
      else if (colorVal == 5){
         setLEDColor(2);
         displayBigTextLine(1, "S[%d][%d] = RED", g_row, ++g_count);
         S[g_row][g_count] = 1;
      }
      else{
         displayBigTextLine(1, "S[%d][%d] = YELLOW", g_row , ++g_count);
         S[g_row][g_count] = 0;
      }
   }

   else if(g_row % 2!= 0){
      if(colorVal == 2){
         setLEDColor(1);
         displayBigTextLine(1,"S[%d][%d] = BLUE", g_row, 4-(++g_count));
         S[g_row][4-g_count] = -1;
      }
      else if(colorVal == 5){
         setLEDColor(2);
         displayBigTextLine(1,"S[%d][%d] = RED", g_row, 4-(++g_count));
         S[g_row][4-g_count] = 1;
      }
      else{
         displayBigTextLine(1,"S[%d][%d] = YELLOW", g_row, 4-(++g_count));
         S[g_row][4-g_count] = 0;
      }
   }
   setLEDColor(0);
   setSpeed(40, 40);
   sleep(200);
}

void go() {
   if(getColorName(c2) == 4)
   {
      setSpeed(g_nMotorSpeedSetting - g_val, g_nMotorSpeedSetting + g_val);
   }
   else
   {
      setSpeed(g_nMotorSpeedSetting + g_val,g_nMotorSpeedSetting - g_val);
   }
   if(g_row == 1)
   {
      if(getColorName(c1) == 4 && g_count != 4)
      {
         g_vertex++;
         setSpeed(12, 10);
         sleep(80);
      }
      else
         g_vertex = 0;
   }
   else if(g_row == 3)
   {
      if(getColorName(c1) == 4 && g_count != 4) g_vertex++;
      else g_vertex = 0;
   }
   else if(g_row == 4)
   {
      if(getColorName(c1) == 4 && g_count != 4) g_vertex++;
      else g_vertex = 0;
   }
   else //g_row : 0 or 2
   {
      if(getColorName(c3) == 4 && g_count != 4) g_vertex++;
      else g_vertex = 0;
   }

   if(g_vertex == 1) //Intersection : 1
   {
      if(g_row == 0 || g_row == 2 || g_row == 4){
         turnForColorSearch();
         sleep(150);
         setSpeed(12, 10);
         sleep(80);
      }
      else
      {
         turnForColorSearch();
         sleep(150);
         setSpeed(10, 12);
         sleep(80);
      }
      storeColor();
   }
}

void turnLeft()
{
	int tmp_r=0, tmp_g=0, tmp_b=0;
   setSpeed(10, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setSpeed(-g_nMotorSpeedSetting * g_rotationOffset, g_nMotorSpeedSetting * g_rotationOffset);
      sleep(10);
   }
   while(1)
   {
    getColorRGB(c2, tmp_r, tmp_g, tmp_b);
    if(tmp_b<18){break;}
    setSpeed(-g_nMotorSpeedSetting * g_rotationOffset, g_nMotorSpeedSetting * g_rotationOffset);

   }
   sleep(100);
   setSpeed(0,0);
   sleep(200);
   g_count = 0;
}

void turnRight()
{
   int tmp_r=0, tmp_g=0, tmp_b=0;
   setSpeed(10,10);
   sleep(100);
   while(getColorName(c3) > 4)
   {
      setSpeed(g_nMotorSpeedSetting * g_rotationOffset, -g_nMotorSpeedSetting * g_rotationOffset);
      sleep(10);
   }
   while(1)
   {
      getColorRGB(c2, tmp_r, tmp_g, tmp_b);
      if(tmp_b<18){break;}
      setSpeed(g_nMotorSpeedSetting * g_rotationOffset, -g_nMotorSpeedSetting * g_rotationOffset);
   }
   sleep(100);
   setSpeed(0, 0);
   sleep(200);
   g_count = 0;
}

void completeSearch()
{
   while(true)
   {
      go();
      if (g_count == 4)
      {
         if(g_row == 4) return;

         if (g_row % 2 == 0)
         {
            setSpeed(35, 30);
            sleep(200);
            turnRight();
         }
         else
         {
            setSpeed(30, 35);
            sleep(200);
            turnLeft();
         }

         g_row++;

         if(g_row%2 == 0)
         {
            while(getColorName(c1) == 6) {
               if(getColorName(c2) == 4) setSpeed(g_nMotorSpeedSetting - g_val, g_nMotorSpeedSetting + g_val);
               else setSpeed(g_nMotorSpeedSetting + g_val, g_nMotorSpeedSetting - g_val);
            }

            turnForColorSearch();
            sleep(150);
            setSpeed(10, 10);
            sleep(80);

            g_count = -1; //It doesn't matter because the storeColor does ++g_count
            storeColor();

            setSpeed(30, 35);
            sleep(200);
            turnLeft();
            setSpeed(-25, -25);
            sleep(100);
         }

         else
         {
            while(getColorName(c3) == 6) {
            	if(getColorName(c2) == 4) setSpeed(g_nMotorSpeedSetting - g_val, g_nMotorSpeedSetting + g_val);
                else setSpeed(g_nMotorSpeedSetting + g_val, g_nMotorSpeedSetting - g_val);
            }
            turnForColorSearch();
            sleep(150);
            setSpeed(10, 10);
            sleep(80);

            g_count = -1; //It doesn't matter because the storeColor does ++g_count
            storeColor();

            setSpeed(35, 30);
            sleep(200);
            turnRight();
            setSpeed(-25, -25);
            sleep(100);
         }
         g_count = 0;
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

void leftTask(){ //Left-hand rotation function used for U, R, D, L functions
   setSpeed(10, 10);
   sleep(100);
   while(getColorName(c1) > 4)
   {
      setSpeed(-g_nMotorSpeedSetting * g_rotationOffset,g_nMotorSpeedSetting * g_rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4) setSpeed(-g_nMotorSpeedSetting * g_rotationOffset,g_nMotorSpeedSetting * g_rotationOffset);
   sleep(100);
   setSpeed(0,0);
   sleep(200);
   g_count = 0;
}

void rightTask(){ //Right-hand rotation function used for U, R, D, L functions
   setSpeed(10, 10);
   sleep(100);
   while(getColorName(c3) > 4)
   {
      setSpeed(g_nMotorSpeedSetting * g_rotationOffset, -g_nMotorSpeedSetting * g_rotationOffset);
      sleep(10);
   }
   while(getColorName(c2) > 4) setSpeed(g_nMotorSpeedSetting * g_rotationOffset, -g_nMotorSpeedSetting * g_rotationOffset);
   sleep(100);
   setSpeed(0,0);
   sleep(200);
   g_count = 0;
}

void goUp(){
   while(getColorName(c1) > 4 && getColorName(c3) > 4){
		if(getColorName(c2) == 4) setSpeed(g_nMotorSpeedSetting - g_val, g_nMotorSpeedSetting + g_val);
		else setSpeed(g_nMotorSpeedSetting + g_val, g_nMotorSpeedSetting - g_val);
   }
   sleep(100);
   setSpeed(30,30);
   sleep(350);
   setSpeed(0,0);
}

void goRight()
{
  rightTask();
  sleep(100);
  goUp();
}

void goLeft(){
   leftTask();
   sleep(100);
   goUp();
}

void goDown(){
   leftTask();
   sleep(100);
   leftTask();
   sleep(100);
   goUp();
}

void moveRobot()
{
	for (int i = 0; i < resultMove.moveCount; i++)
	{
		if (resultMove.moves[i] == Up) goUp();
		else if (resultMove.moves[i] == Down) goDown();
		else if (resultMove.moves[i] == Left) goLeft();
		else if (resultMove.moves[i] == Right) goRight();
      setSpeed(0,0);
		sleep(1000);
	}
}
