#include <stdio.h>
#include "main.h"
#include "SqQueue.h"

Status InitQueue(SqQueue* Q) {
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base)
	{
		exit(OVERFLOW);
	}
	Q->front = Q->rear = 0;
	return OK;
}

int QueueLength(SqQueue Q) {
	return ((Q.rear - Q.front + MAXQSIZE) % MAXQSIZE);
}

Status EnQueue(SqQueue* Q, QElemType x) {
	if ((Q->rear + 1) % MAXQSIZE == Q->front) {
		return ERROR;
	}
	Q->base[Q->rear] = x;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue* Q, QElemType* x) {
	if (Q->rear == Q->front)
	{
		return ERROR;
	}
	*x = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

QElemType GetHead(SqQueue Q) {
	if (Q.rear != Q.front)
	{
		return Q.base[Q.front];
	}
	return ERROR;
}