#pragma config(Sensor, S1, c1, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)
#define White 6
#define Yellow 4
#define Red 5
#define Green 2

int nMotorSpeedSetting = 35, vertex = 0, count = 0, row = 0, val = 5, colorVal = 0, init = 0;
int S[5][5];
int nr=0,ng=0, nb=0;

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
   int i = 0;
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
   sleep(30000);
}

task main()
{
   completeSearch();
   setMotorSpeed(lm,30);
   setMotorSpeed(rm,30);
   sleep(350);
   turnLeft();
   turnLeft();

   sleep(2000);
   DisplayMap();
   sleep(10000);
}
