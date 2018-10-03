#include "tree.h"
#include <stdio.h>
#include <limits.h>

const int INDENT = 3;
int isTreeEmpty(Node *node) {
	return (node == NULL);
}

void newNode(Node** parent, const int data) {
	Node *tmpNode = (Node *) malloc(sizeof(Node));
	//инициализация пустого узла
	tmpNode->data = data;
	tmpNode->parent = NULL;
	tmpNode->oldBro = NULL;
	tmpNode->lilBro = NULL;
	tmpNode->son = NULL;
	if (isTreeEmpty(*parent)) {
		//еслисоздается корень
		//т.е если нет родителя
		*parent = tmpNode;
		return;
	}

	//очевидно что родителем будет родитель
	tmpNode->parent = (*parent);
	//поиск старшего брата
	Node *tmpBro = NULL;
	if (isTreeEmpty((*parent)->son)) {
		(*parent)->son = tmpNode;
		//если он единственный сын
	} else {
		//поиск самого младцего брата из присутвующих в родителе
		tmpBro = (*parent)->son;
		while (!isTreeEmpty(tmpBro->lilBro))
			tmpBro = tmpBro->lilBro;
		tmpNode->oldBro = tmpBro;
		tmpBro->lilBro = tmpNode;
	}
}

void KLP(Node *node, const int level) {

	if (isTreeEmpty(node)) {
		printf("Дерево пусто\n");
		return;
	}
	printf("%*s%d\n", level * INDENT, "", node->data);
	if (!isTreeEmpty(node->son))
		KLP(node->son, level + 1);
	if (!isTreeEmpty(node->lilBro))
		KLP(node->lilBro, level);
}

int max(int a, int b) {
	return (a > b ? a : b);
}

int treeMaxPow(Node *node) {
	if (isTreeEmpty(node))
		return INT_MIN;
	int cnt = 0;
	Node* current = node;
	while(!isTreeEmpty(current)) {
		cnt++;
		current = current->lilBro;
	}
	return max(cnt,
			max(treeMaxPow(node->son), treeMaxPow(node->lilBro)));
}

int treeNodeDFS(Node *node, const int value) {
	if (isTreeEmpty(node))
		return 0;
	if (node->data == value)
		return 1;
	int ret = treeNodeDFS(node->son, value);
	return (ret) ? (ret + 1) : treeNodeDFS(node->lilBro, value);
}

Node *findNodeByValue(Node **node, const int value) {
//ПОИСК УЗЛА ПО ЗНАЧЕНИЮ
//если узла не встречено,то функция вернет NULL, иначе ссылку на узел
//у узлов значения HE могут повторяться, поэтому первый встреченный с заданным значением возвращается
	Node *tmpNode = NULL;
	Node *ret = NULL;		//изменяется если непустое дерево

//найденный узел прерывает дальнейшее вложение функций
	if ((*node)->data == value)
		return *node;
	if (!isTreeEmpty((*node)->lilBro)) {
		tmpNode = findNodeByValue(&(*node)->lilBro, value);
		//изменяется если непустое дерево
		if (!isTreeEmpty(tmpNode))
			ret = findNodeByValue(&(*node)->lilBro, value);
	}
	if (!isTreeEmpty((*node)->son)) {
		tmpNode = findNodeByValue(&(*node)->son, value);
		if (!isTreeEmpty(tmpNode))
			ret = findNodeByValue(&(*node)->son, value);
	}
//все вложенные функции будут возвращать найденный узел
//в итоге он "всплывает"
//если узла не встречено то  функция вернет NULL
	return ret;
}
void destroyTree(Node **node) {
//уничтожение всего, что соприкасается снизу с узлом
	if (isTreeEmpty(*node))
		return;
	destroyTree(&(*node)->lilBro);
	destroyTree(&(*node)->son);
	free(*node);
	*node = NULL;
}
int addNode(Node** node, const int parentValue, const int data) {

	if (isTreeEmpty(*node))
		return 2;		//printf("Дерево пусто\n");

	Node* tmpNode = findNodeByValue(node, parentValue);
	if (isTreeEmpty(tmpNode))
		return 1;		//printf("Такого родителя нет\n");
	if (!isTreeEmpty(findNodeByValue(node, data)))
		return 3;		//printf("Такой элемент уже есть\n");printf("Такой элемент уже есть\n");
	newNode(&tmpNode, data);
	return 0;			//printf("%d стал сыном %d\n", data2, data1);

}
int removeNode(Node **node, const int data) {
//удаление узла
	Node* tmpNode = NULL;
	if (isTreeEmpty(*node))
		return 2;		//printf("Дерево пусто\n");

	tmpNode = findNodeByValue(node, data);
	if (isTreeEmpty(tmpNode))
		return 1;

	if (isTreeEmpty(tmpNode->parent)) {
		//если у узла нет родителя, т.е он корень то уничтожить все дерево
		destroyTree(node);
		return 0;
	}

	if (!isTreeEmpty(tmpNode->lilBro))
		tmpNode->lilBro->oldBro = tmpNode->oldBro;
	if (isTreeEmpty(tmpNode->oldBro))
		tmpNode->parent->son = tmpNode->lilBro;
	else
		tmpNode->oldBro->lilBro = tmpNode->lilBro;

	if (!isTreeEmpty(tmpNode->son))
		destroyTree(&tmpNode->son);
	free(tmpNode);
	tmpNode = NULL;
	return 0;
}

