#include "define.c"

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
	Point cur;
	Point robot;
	MoveArray moveArray;
	short v;
} Element;

typedef struct
{
	byte top;
	Element data[MAX_STACK_SIZE];
} Stack;

typedef struct
{
	byte count;
	Point redArray[MAX_RED_PATCH];
} RedSet;
