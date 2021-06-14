#ifndef SQQUEUE_H
#define SQQUEUE_H

#define MAXQSIZE 100

typedef struct {
	QElemType* base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue* Q, QElemType x);
Status DeQueue(SqQueue* Q, QElemType* x);
QElemType GetHead(SqQueue Q);

#endif