#include <stdio.h>
#define White 6
#define Yellow 4
#define Red 5
#define Green 2

#define Up 1
#define Down 2
#define Left 3
#define Right 4

#define MIN -100
#define MAX_MOVE_COUNT 20
#define MAX_RED_PATCH 5
#define MAX_STACK_SIZE 30

// error code
#define Error -99

typedef struct
{
	int r;
	int c;
} Point;

typedef struct
{
	int moveCount;
	int moves[MAX_MOVE_COUNT];
} MoveArray;

int g_nMotorSpeedSetting = 45, g_vertex = 0, g_count = 0, g_row = 0, g_val = 6, g_init = 0;
float g_rotationOffset = 0.4;
int S[5][5] = {
	{-1, 0, -2, -1, -1},
	{-2, 0, -2, -1, -1},
	{0, -1, -2, 0, -1},
	{0, -1, -2, -1, -1},
	{-1, -1, -1, -1, -1}
};
int dp[5][5];
int resultDp[5][5];
int maxScore = MIN;
MoveArray resultMove;

int absMove(Point robot, Point next)
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

void initDpTable()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			dp[i][j]= MIN;
	dp[4][4] = 0;
}

void initPoint(Point *point, int r, int c)
{
	point->r = r;
	point->c = c;
}

void initMoveArray(MoveArray *moveArray, int moveCount, int *moves)
{
	moveArray->moveCount = moveCount;
	for (int i = 0; i < moveCount; i++)
		moveArray->moves[i] = moves[i];
}

void getResultDpTable(Point curPoint, Point robotDir, MoveArray curMoveArray)
{
	Point nextPoint, nextDir;
	MoveArray nextMoveArray;
	int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	int curScore, prevWeight, nextWeight, nextScore;
	if (curPoint.r == 0 && curPoint.c == 0)
	{
		if (dp[0][0] > maxScore)
		{
			maxScore = dp[0][0];
			printf("maxScore is updated: %d\n", maxScore);
			initMoveArray(&resultMove, curMoveArray.moveCount, curMoveArray.moves);
			printf("moves: [");
			for (int i = 0; i < resultMove.moveCount - 1; i++)
				printf("%d, ", resultMove.moves[i]);
			printf("%d]\n", resultMove.moves[resultMove.moveCount - 1]);
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		initPoint(&nextDir, directions[i][0], directions[i][1]);
		initPoint(&nextPoint, curPoint.r  + nextDir.r, curPoint.c + nextDir.c);
		initMoveArray(&nextMoveArray, curMoveArray.moveCount, curMoveArray.moves);
		nextMoveArray.moves[nextMoveArray.moveCount++] = absMove(robotDir, nextDir);
		if (nextPoint.r < 0 || nextPoint.r >= 5 || nextPoint.c < 0 || nextPoint.c >= 5) continue;
		prevWeight = S[nextPoint.r][nextPoint.c];
		nextWeight = prevWeight;
		curScore = dp[nextPoint.r][nextPoint.c];
		nextScore = dp[curPoint.r][curPoint.c] + prevWeight;
		if (nextWeight == 0) nextWeight = -1;
		if (dp[nextPoint.r][nextPoint.c] < nextScore)
		{
			S[nextPoint.r][nextPoint.c] = nextWeight;
			dp[nextPoint.r][nextPoint.c] = nextScore;
			getResultDpTable(nextPoint, nextDir, nextMoveArray);
			S[nextPoint.r][nextPoint.c] = prevWeight;
			dp[nextPoint.r][nextPoint.c] = curScore;
		}
	}
}

void getMoveArray()
{
	Point curPoint, robotDir;
	MoveArray curMoveArray;
	int moves[MAX_MOVE_COUNT];
	initPoint(&curPoint, 4, 4);
	initPoint(&robotDir, 0, -1);
	initMoveArray(&curMoveArray, 0, moves);
	getResultDpTable(curPoint, robotDir, curMoveArray);
}

int main()
{
	initDpTable();
	getMoveArray();
}