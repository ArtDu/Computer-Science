#ifndef TREE_H
#define TREE_H

#include <stdlib.h>


typedef struct _Node
{
	int data;
	struct _Node *parent;
	struct _Node *oldBro;
	struct _Node *lilBro;
	struct _Node *son;
} Node;

Node *treeAddNode(Node **node, const int value);
Node *treeFindNode(Node **node, const int value);
int treeRemoveNode(Node **node, const int value);
void treeDestroy(Node **node);

#endif
