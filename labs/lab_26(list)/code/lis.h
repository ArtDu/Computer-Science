#ifndef LIS_H
#define LIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POOL_SIZE 10

typedef struct _data_type {
	int key;
	float value;
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
	Item* top;
	Item data[POOL_SIZE+1];

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
void List_destroy(List* list);
bool List_empty(const List* list);
int List_Size(const List* list);


//elements fuctions
List_type element_List_by_num(const List* list, int num);
void element_List_store(const List* list, int num, List_type t);
void List_insert_by_num(List* list, int i, List_type t);

#endif
