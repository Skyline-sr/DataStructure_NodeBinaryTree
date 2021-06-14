#ifndef MAIN_H
#define MAIN_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int TElemType;
typedef int Mode;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
	int depth;
}BiTNode, * BiTree;

typedef BiTree SElemType;
typedef BiTree QElemType;

#endif

