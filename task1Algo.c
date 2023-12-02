void initWGraph()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (S[i][j] == 0) wGraph[i][j] = -1;
			else if (S[i][j] == 1) wGraph[i][j] = 10;
			else if (S[i][j] == -1) wGraph[i][j] = -10;
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
	if ((wGraph[next.r][next.c] == 10) && isVisited(next, v))
		return dp[5 * prev.r + prev.c][v] - 1;
	return dp[5 * prev.r + prev.c][v] + wGraph[next.r][next.c];
}

int handleRed(Point cur, int v)
{
	if ((wGraph[cur.r][cur.c] != 10) || isVisited(cur, v))
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
			if (wGraph[i][j] == 10)
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
	byte directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
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

void printMove()
{
	char converts[5] = {0, 'U', 'D', 'L', 'R'};
	for (int i = 0; i < resultMove.moveCount / 2; i++) displayStringAt(i * 10, 100, "%c ",  converts[resultMove.moves[i]]);
	for (int i = resultMove.moveCount / 2; i < resultMove.moveCount; i++) displayStringAt((i - resultMove.moveCount / 2) * 10, 90, "%c ",  converts[resultMove.moves[i]]);
}

void printMaxScore()
{
	int score = 0;
	int v = 0;
	Point curPoint, nextPoint, robotDir, nextDir;
	initPoint(curPoint, 4, 4);
	initPoint(robotDir, 0, -1);
	for (int i = 0; i < resultMove.moveCount; i++)
	{
		if (robotDir.r == 0 && robotDir.c == 1)
		{
			if (resultMove.moves[i] == Up) initPoint(nextDir, 0, 1);
			if (resultMove.moves[i] == Down) initPoint(nextDir, 0, -1);
			if (resultMove.moves[i] == Left) initPoint(nextDir, -1, 0);
			if (resultMove.moves[i] == Right) initPoint(nextDir, 1, 0);
		}
		if (robotDir.r == 0 && robotDir.c == -1)
		{
			if (resultMove.moves[i] == Up) initPoint(nextDir, 0, -1);
			if (resultMove.moves[i] == Down) initPoint(nextDir, 0, 1);
			if (resultMove.moves[i] == Left) initPoint(nextDir, 1, 0);
			if (resultMove.moves[i] == Right) initPoint(nextDir, -1, 0);
		}
		if (robotDir.r == 1 && robotDir.c == 0)
		{
			if (resultMove.moves[i] == Up) initPoint(nextDir, 1, 0);
			if (resultMove.moves[i] == Down) initPoint(nextDir, -1, 0);
			if (resultMove.moves[i] == Left) initPoint(nextDir, 0, 1);
			if (resultMove.moves[i] == Right) initPoint(nextDir, 0, -1);
		}
		if (robotDir.r == -1 && robotDir.c == 0)
		{
			if (resultMove.moves[i] == Up) initPoint(nextDir, -1, 0);
			if (resultMove.moves[i] == Down) initPoint(nextDir, 1, 0);
			if (resultMove.moves[i] == Left) initPoint(nextDir, 0, -1);
			if (resultMove.moves[i] == Right) initPoint(nextDir, 0, 1);
		}
		initPoint(nextPoint, curPoint.r + nextDir.r, curPoint.c + nextDir.c);
		if (!(S[nextPoint.r][nextPoint.c] == 1 && isVisited(nextPoint, v)))
			score += S[nextPoint.r][nextPoint.c];
		v = ((1 << findRedSeq(nextPoint)) | v);
		initPoint(curPoint, nextPoint.r, nextPoint.c);
		initPoint(robotDir, nextDir.r, nextDir.c);
	}
	displayBigTextLine(1, "maxCount: %d", score);
}
