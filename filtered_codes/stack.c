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

typedef struct
{
	byte score;
	byte moveCount;
} Dp1Elem;

typedef struct
{
	Point cur;
	Point robot;
	MoveArray moveArray;
	byte v;
} Element;

typedef struct
{
	byte top;
	Element data[MAX_STACK_SIZE];
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, Element e);
void pop(Stack *s, Element &e);

void initStack(Stack *s)
{
	s->top=-1;
}

int isFull(Stack *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

int isEmpty(Stack *s)
{
	return (s->top == -1);
}

void push(Stack *s, Element e)
{
	if(isFull(s)) return;
	(s->top)++;
	s->data[s->top].cur.r = e.cur.r;
	s->data[s->top].cur.c = e.cur.c;
	s->data[s->top].robot.r = e.robot.r;
	s->data[s->top].robot.c = e.robot.c;
	s->data[s->top].moveArray.moveCount = e.moveArray.moveCount;
	for (int i = 0; i < s->data[s->top].moveArray.moveCount; i++)
		s->data[s->top].moveArray.moves[i] = e.moveArray.moves[i];
	s->data[s->top].v = e.v;
}

void pop(Stack *s, Element &e)
{
	if(isEmpty(s)) return;
	e.cur.r = s->data[s->top].cur.r;
	e.cur.c = s->data[s->top].cur.c;
	e.robot.r = s->data[s->top].robot.r;
	e.robot.c = s->data[s->top].robot.c;
	e.moveArray.moveCount = s->data[s->top].moveArray.moveCount;
	for (int i = 0; i < e.moveArray.moveCount; i++)
		e.moveArray.moves[i] = s->data[s->top].moveArray.moves[i];
	e.v = s->data[s->top].v;
  (s->top)--;
}
