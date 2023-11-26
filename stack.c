#include "struct.c"

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
