#ifndef SQQUEUE_H
#define SQSTACK_H

#define MAXSIZE 100

typedef struct {
	SElemType* top;
	SElemType* base;
	int stacksize;
}SqStack;

Status InitStack(SqStack* S);
Status StackEmpty(SqStack S);
int StackLength(SqStack S);
Status ClearStack(SqStack* S);
Status DestroyStack(SqStack* S);
Status Push(SqStack* S, SElemType x);
Status Pop(SqStack* S, SElemType* x);
Status GetTop(SqStack* S, SElemType* x);

#endif

