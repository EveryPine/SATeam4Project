// 구조체
typedef struct
{
	byte r;
	byte c;
} Point;

typedef struct
{
	byte moveCount;
	byte moves[MAX_MOVE_COUNT];
} MoveArray;

typedef struct
{
	byte count;
	Point redArray[MAX_RED_PATCH];
} RedSet;

// 변수
MoveArray moveSeq[5];
RedSet red;
int weightGraph[5][25]; // weightGraph[i]: i번째 패치 가중치 그래프
int finishWGraph[5][5]; // 도착점을 기준으로 한 가중치 그래프
int visited = 0;

// 함수
void initRedSet(); // 빨간 패치 순서 및 위치 초기화
void getWGraph(int redIndex); // i번째 패치 가중치 그래프 초기화
void getWGraphWithBfs(Point curPoint, float w);
int getRedDist(int i, Point curPoint); // i번째 빨간 패치와 현재 위치 사이의 최소 이동 횟수 반환
// return minDist;
int minDist(Point curPoint); // 현재 위치에서 최소로 이동가능한 빨간 패치 인덱스 반환
// return index;

void moveRobot(MoveArray *move); // 입력받은 이동 구조체대로 로봇을 움직인다. -> 로봇센싱
void handleRed(int i);

void getWGraph(int redIndex)
{
	// 그래프 초기화
	for (int i = 0; i < 25; i++)
		weightGraph[redIndex][i] = -1;
	
	getWGraphWithBfs(red.redArray[redIndex]);
}

void getWGraphWithBfs(Point curPoint)
{
	int directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
}