#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "SqStack.h"

#define DE_BITREE 0
#define NUM_BITREE 1
#define DE_BITREE 0
#define DE_BITREE 0
static int bitree_node_number = 0;

Status InitBiTree(BiTree* T);
Status DestroyBiTree(BiTree* T);
Status BiTreeEmpty(BiTree T);
Status InsertRoot(BiTree* T, TElemType x);
int BiTreeNodeNumber(BiTree T);
int BiTreeDepth(BiTree T);

void PreOrderTraverse_Recursion(BiTree* T, Mode mode);
void InOrderTraverse_Recursion(BiTree* T, Mode mode);
void PostOrderTraverse_Recursion(BiTree* T, Mode mode);
void PreOrderTraverse_NonRecursion(BiTree* T, Mode mode);
void InOrderTraverse_NonRecursion(BiTree* T, Mode mode);
void PostOrderTraverse_NonRecursion(BiTree* T, Mode mode);

void DataHandle(BiTree* Node, Mode mode);


void main() {

}

Status InitBiTree(BiTree* T) {  //创建空树
	if (*T)
	{
		return ERROR;
	}
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
	return OK;
}

Status InsertChild() {
	
}

int BiTreeNodeNumber(BiTree T) {
	int number;
	bitree_node_number = 0;
	PreOrderTraverse_Recursion(&T, NUM_BITREE);
	number = bitree_node_number;
	return number;
}

int BiTreeDepth(BiTree T) {
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

void DataHandle(BiTree* Node, Mode mode) {
	BiTree p;
	p = *Node;
	printf("%d", p->data);
	switch (mode)
	{
	case DE_BITREE:
		free(p);
		break;
	case NUM_BITREE:
		bitree_node_number++;
		break;
	default:
		break;
	}
}