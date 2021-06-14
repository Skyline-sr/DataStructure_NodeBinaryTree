#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "SqStack.h"
#include "SqQueue.h"

/*数据处理Mode*/
#define NOHANDLE_BITREE -1
#define DE_BITREE 0
#define NUM_BITREE 1
#define INSERT_BITREE 2
#define PRINT_BITREE 3
#define PRINT_TRAVERSE_BITREE 4

#define LC 0
#define RC 1
#define MAXSIZE_LINE 100

static int bitree_node_number = 0;
static int bitree_depth = 0;
static BiTree Node_Find;
static TElemType Node_Search;
static int bitree_line_number[MAXSIZE_LINE] = { 0 };
static int bitree_line_number_fordatahandle[MAXSIZE_LINE] = { 0 };

Status InitBiTree(BiTree* T);
Status DestroyBiTree(BiTree* T);
Status BiTreeEmpty(BiTree T);
Status InsertRoot(BiTree* T, TElemType x);
Status InsertChild(BiTree* T, TElemType Node, TElemType x, int depth, int l_or_r);
int BiTreeNodeNumber(BiTree T);
int BiTreeDepth(BiTree T);
void PrintBiTree(BiTree T);

void PreOrderTraverse_Recursion(BiTree* T, Mode mode);
void InOrderTraverse_Recursion(BiTree* T, Mode mode);
void PostOrderTraverse_Recursion(BiTree* T, Mode mode);
void PreOrderTraverse_NonRecursion(BiTree* T, Mode mode);
void InOrderTraverse_NonRecursion(BiTree* T, Mode mode);
void PostOrderTraverse_NonRecursion(BiTree* T, Mode mode);

void LevelOrderTraverse(BiTree* T, Mode mode);

void DataHandle(BiTree* Node, Mode mode);


void main() {
	BiTree T;
	InitBiTree(&T);
	InsertRoot(&T, 1);
	InsertChild(&T, 1, 2, 2, LC);
	InsertChild(&T, 1, 3, 2, RC);
	InsertChild(&T, 2, 4, 3, RC);
	PreOrderTraverse_Recursion(&T, NOHANDLE_BITREE);
	PreOrderTraverse_Recursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	PreOrderTraverse_NonRecursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	InOrderTraverse_Recursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	InOrderTraverse_NonRecursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	PostOrderTraverse_Recursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	PostOrderTraverse_NonRecursion(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	LevelOrderTraverse(&T, PRINT_TRAVERSE_BITREE);
	printf("\n\n");
	PrintBiTree(T);
}

Status InitBiTree(BiTree* T) {  //创建空树
	*T = NULL;
	return OK;
}

Status DestroyBiTree(BiTree* T) {
	if (*T == NULL)
	{
		return ERROR;
	}
	PreOrderTraverse_Recursion(T, DE_BITREE);
	*T = NULL;
	return OK;
}

Status BiTreeEmpty(BiTree T) {
	if (T)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

Status InsertRoot(BiTree* T, TElemType x) {
	if (*T)
	{
		return ERROR;
	}
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = x;
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	(*T)->depth = 1;
	bitree_depth = 1;
	bitree_line_number[1]++;
	return OK;
}

Status InsertChild(BiTree* T, TElemType Node, TElemType x, int depth, int l_or_r) {
	if ((*T) == NULL)
	{
		return ERROR;
	}
	BiTree p;
	Node_Search = Node;
	PreOrderTraverse_Recursion(T, INSERT_BITREE);
	if (Node_Find)
	{
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = x;
		p->depth = depth;
		p->lchild = p->rchild = NULL;
		if (!l_or_r)
		{
			Node_Find->lchild = p;
		}
		else
		{
			Node_Find->rchild = p;
		}
		bitree_line_number[depth]++;
	}
	Node_Search = -1;
	Node_Find = NULL;
}

int BiTreeNodeNumber(BiTree T) {
	int number;
	bitree_node_number = 0;
	PreOrderTraverse_Recursion(&T, NUM_BITREE);
	number = bitree_node_number;
	return number;
}

int BiTreeDepth(BiTree T) {
	LevelOrderTraverse(&T, NOHANDLE_BITREE);
	return bitree_depth;
}

void PrintBiTree(BiTree T) {
	LevelOrderTraverse(&T, PRINT_BITREE);
}

/*--------------------------------------------------------------------*/

void PreOrderTraverse_Recursion(BiTree* T, Mode mode) {
	if ((*T) == NULL)
	{
		return;
	}
	DataHandle(T, mode);
	PreOrderTraverse_Recursion(&((*T)->lchild), mode);
	PreOrderTraverse_Recursion(&((*T)->rchild), mode);
}

void InOrderTraverse_Recursion(BiTree* T, Mode mode) {
	if ((*T) == NULL)
	{
		return;
	}
	PreOrderTraverse_Recursion(&((*T)->lchild), mode);
	DataHandle(T, mode);
	PreOrderTraverse_Recursion(&((*T)->rchild), mode);
}

void PostOrderTraverse_Recursion(BiTree* T, Mode mode) {
	if ((*T) == NULL)
	{
		return;
	}
	PreOrderTraverse_Recursion(&((*T)->lchild), mode);
	PreOrderTraverse_Recursion(&((*T)->rchild), mode);
	DataHandle(T, mode);
}

/*--------------------------------------------------------------------*/

void PreOrderTraverse_NonRecursion(BiTree* T, Mode mode) {
	SqStack S;
	BiTree p, q;
	InitStack(&S);
	p = (*T);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			DataHandle(&p, mode);
			Push(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop(&S, &q);
			p = q->rchild;
		}
	}
}

void InOrderTraverse_NonRecursion(BiTree* T, Mode mode) {
	SqStack S;
	BiTree p, q;
	InitStack(&S);
	p = (*T);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop(&S, &q);
			DataHandle(&q, mode);
			p = q->rchild;
		}
	}
}

void PostOrderTraverse_NonRecursion(BiTree* T, Mode mode) {
	SqStack S;
	BiTree p, q;
	Status node_status[MAXSIZE];
	InitStack(&S);
	p = (*T);
	while (p || !StackEmpty(S))
	{
		while (p)
		{
			Push(&S, p);
			p = p->lchild;
			node_status[StackLength(S)] = 1;
		}
		if (!StackEmpty(S))
		{
			Pop(&S, &q);
			if (node_status[StackLength(S) + 1] == 1)
			{
				p = q->rchild;
				node_status[StackLength(S) + 1]++;
				Push(&S, q);
			}
			else if (node_status[StackLength(S) + 1] == 2)
			{
				DataHandle(&q, mode);
				p = NULL;
			}
			else;
		}
	}
}

/*--------------------------------------------------------------------*/

void LevelOrderTraverse(BiTree* T, Mode mode) {
	BiTree p;
	SqQueue Q;
	if ((*T) == NULL)
	{
		return;
	}
	InitQueue(&Q);
	EnQueue(&Q, *T);
	while (Q.front != Q.rear)
	{
		DeQueue(&Q, &p);
		DataHandle(&p, mode);
		if (p->lchild)
		{
			EnQueue(&Q, p->lchild);
		}
		if (p->rchild)
		{
			EnQueue(&Q, p->rchild);
		}
	}
	bitree_depth = p->depth;
}

/*--------------------------------------------------------------------*/

void DataHandle(BiTree* Node, Mode mode) {
	BiTree p;
	p = *Node;
	switch (mode)
	{
	case DE_BITREE:
		free(p);
		break;
	case NUM_BITREE:
		bitree_node_number++;
		break;
	case INSERT_BITREE:
		if (Node_Search == p->data)
		{
			Node_Find = p;
		}
		break;
	case PRINT_BITREE:
		printf("%d ", p->data);
		bitree_line_number_fordatahandle[p->depth]++;
		if (bitree_line_number_fordatahandle[p->depth] == bitree_line_number[p->depth])
		{
			printf("\n");
			bitree_line_number_fordatahandle[p->depth] = 0;
		}
		break;
	case PRINT_TRAVERSE_BITREE:
		printf("%d ", p->data);
		break;
	default:
		break;
	}
}