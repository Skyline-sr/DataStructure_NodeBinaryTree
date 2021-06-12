#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "SqStack.h"

Status InitStack(SqStack* S)
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base)
	{
		exit(OVERFLOW);
	}
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return OK;
}

Status StackEmpty(SqStack S) {
	if (S.top == S.base)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int StackLength(SqStack S) {
	return (S.top - S.base);
}

Status ClearStack(SqStack* S) {
	if (S->base)
	{
		S->top == S->base;
		return OK;
	}
	return ERROR;
}

Status DestroyStack(SqStack* S) {
	if (S->base)
	{
		free(S->base);
		S->base = S->top = NULL;
		S->stacksize = 0;
		return OK;
	}
	return ERROR;
}

Status Push(SqStack* S, SElemType x) {
	if (StackLength(*S) == S->stacksize)
	{
		printf("栈已满！\n");
		return ERROR;
	}
	*(S->top) = x;
	S->top++;
	return OK;
}

Status Pop(SqStack* S, SElemType* x) {
	if (S->top == S->base)
	{
		printf("栈为空，无元素出栈！\n");
		return ERROR;
	}
	S->top--;
	*x = *(S->top);
	return OK;
}

Status GetTop(SqStack* S, SElemType* x) {
	if (S->top == S->base)
	{
		printf("栈为空！\n");
		*x = -1;
		return ERROR;
	}
	*x = *(S->top - 1);
	return OK;
}

void PrintStack(SqStack S) {
	int length, i;
	length = StackLength(S);
	printf("栈中的元素如下：\n");
	for (i = length; i > 0; i--)
	{
		S.top--;
		printf("第%d个位置的元素：%d\n", i, *S.top);
	}
}
