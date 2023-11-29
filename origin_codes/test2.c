// 1단계를 기준으로 정리된 그래프를 2단계 조건에 맞게 변환한다.
void convertGraph()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (S[i][j] == 0) S[i][j] = -1; // 0: 패치 없음, -1으로 변경
			else if (S[i][j] == 1) S[i][j] = 4; // 1: 빨간 패치, 방문 보너스 5점에서 이동 패널티 1점을 감점한 4로 변경
			else if (S[i][j] == -1) S[i][j] = -4; // -1: 초록 패치, 방문 패널티 3점에서 이동 패널티 1점을 추가한 -4로 변경
			else S[i][j] = Error; // 디버그용 코드
		}
}

// 2차원 Dp 배열을 초기화한다.
void initDpTable()
{
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < (1 << MAX_RED_PATCH); j++)
			dp[i][j] = MIN;
	dp[24][0] = 0;
}

// 로봇이 바라보는 방향과 가고자 하는 방향을 입력받아 적절한 이동 방향 정수를 반환한다.
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

// 위치를 입력받아 이곳에 있는 빨간 패치의 번호를 반환한다.
byte findRedSeq(Point cur)
{
	for (byte i = 0; i < red.count; i++)
	{
		if ((red.redArray[i].r == cur.r) && (red.redArray[i].c == cur.c))
			return i;
	}
    // 빨간 패치가 없는 위치를 입력받으면 예외를 발생시킴
	setException(1);
	return Error;
}

// 위치에 있는 빨간 패치의 방문 여부를 반환한다.
// true: 방문함
// false: 방문하지 않음
bool isVisited(Point cur, int v)
{
	if (((1 << findRedSeq(cur)) & v) > 0) return true;
	return false;
}

// v 방문 상태 정수인 상태에서 이전 위치(prev)에서 다음 위치(next)로 이동할 때
// 얻게 될 점수를 반환한다.
byte getNextScore(Point prev, Point next, int v)
{
	if ((S[next.r][next.c] == 4) && isVisited(next, v))
		return dp[5 * prev.r + prev.c][v] - 4;
	return dp[5 * prev.r + prev.c][v] + S[next.r][next.c];
}

// 위치에 있는 빨간 패치를 아직 방문하지 않았다면 방문처리 한 방문 상태 정수를 반환한다.
int handleRed(Point cur, int v)
{
	if ((S[cur.r][cur.c] != 4) || isVisited(cur, v))
		return v;
	return ((1 << findRedSeq(cur)) | v);
}

// 빨간 패치 순서를 위치와 함께 번호를 매긴다.
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

// Point 구조체 초기화 함수
void initPoint(Point &point, byte r, byte c)
{
	point.r = r;
	point.c = c;
}

// MoveArray 구조체 초기화 함수
void initMoveArray(MoveArray &moveArray, byte moveCount, byte *moves)
{
	moveArray.moveCount = moveCount;
	for (int i = 0; i < moveCount; i++)
		moveArray.moves[i] = moves[i];
}

// Element 구조체 초기화 함수
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

// 최대 점수를 얻을 수 있는 방법 배열을 구하여 resultMove에 저장한다.
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
	initElement(e, 4, 4, 0, -1, 0, curMove.moves, 0); // 
	push(&s, e);

    // 스택이 빌 때까지 반복
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
				else if (nextMove.moveCount < MAX_MOVE_COUNT)
				{
					initElement(e, next.r, next.c, dir.r, dir.c, nextMove.moveCount, nextMove.moves, nv);
					push(&s, e);
				}
			}
		}
	}
}

// (디버그용 함수) 로봇 이동 배열을 출력한다.
void printMove()
{
	char converts[5] = {0, 'U', 'D', 'L', 'R'};
	for (int i = 0; i < resultMove.moveCount / 2; i++)
		displayStringAt(i * 10, 100, "%c ",  converts[resultMove.moves[i]]);
	for (int i = resultMove.moveCount / 2; i < resultMove.moveCount; i++)
		displayStringAt((i - resultMove.moveCount / 2) * 10, 90, "%c ",  converts[resultMove.moves[i]]);
}

// 최대 점수를 출력한다.
void printMaxScore()
{
	byte mx = MIN;
	for (int i = 0; i < 1 << MAX_RED_PATCH; i++)
		if (mx < dp[0][i]) mx = dp[0][i];
	displayBigTextLine(1, "maxCount: %d", mx);
}