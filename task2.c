#pragma config(Sensor, S1,     c1,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     c2,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)
#include "define.c"
#include "struct.c"

int g_nMotorSpeedSetting = 45, g_vertex = 0, g_count = 0, g_row = 0, g_val = 6, g_init = 0;
float g_rotationOffset = 0.4;
int S[5][5];
byte dp[25][1 << MAX_RED_PATCH];
RedSet red;
MoveArray resultMove;

#include "colorStore.c"
#include "task2Algo.c"

task main()
{
  completeSearch();
  setSpeed(30, 30);
  sleep(350);
  turnLeft();
  turnLeft();
  sleep(500);

  eraseDisplay();
  DisplayMap();
  sleep(1000);
  convertGraph();
  initDpTable();
  getMoveArray();
  moveRobot();
  eraseDisplay();
  printMaxScore();
  sleep(10000);
}
