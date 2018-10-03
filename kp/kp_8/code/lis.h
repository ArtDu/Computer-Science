#ifndef LIS_H
#define LIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 100

typedef struct _data_type {
	char lt[100];
} List_type;

typedef struct _Item {
	struct _Item* prev;
	struct _Item* next;
	List_type data;
} Item;

typedef struct {
	Item* node;
} Iterator;

typedef struct _List {
	Item* head;
	int size;
} List;

//functions for work with iterators
bool it_List_equal(const Iterator* lhs, const Iterator* rhs);
Iterator it_List_next(Iterator* i);
Iterator it_List_prev(Iterator* i);
List_type it_List_fetch(Iterator* i);
void it_List_store(Iterator* i, List_type t);

//functions for work with List type
void List_create(List *deq);
Iterator List_top_front(const List* list);
Iterator List_top_back(const List* list);
Iterator List_insert(List* list, Iterator* i, List_type t);
Iterator List_delete(List* list, Iterator* i);
//void List_destroy(List* list);
bool List_empty(const List* list);
int List_Size(const List* list);

/*
Not standart functions
*/
void List_print(List *list);
void List_task(List* list, char lbord[100], char rbord[100]);
#endif
