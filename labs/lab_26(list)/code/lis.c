#include "lis.h"


//functions for work with iterators
bool it_List_equal(const Iterator* lhs, const Iterator* rhs) {
	return lhs->node == rhs->node;
}

Iterator it_List_next(Iterator* i) {
	i->node = i->node->next;
}
Iterator it_List_prev(Iterator* i) {
	i->node = i->node->prev;
}
List_type it_List_fetch(Iterator* i){
	return i->node->data;
}
void it_List_store(Iterator* i, List_type t) {
	i->node->data = t;
}
 


//functions for work with List type
void List_create(List* list) {

	list->size = 0;
	int i;
	for(i = 0; i < POOL_SIZE; i++) {
		list->data[i].next = &(list->data[i+1]);
	}
	list->head = &(list->data[POOL_SIZE]);
	list->head->prev = list->head->next = list->head;
	list->top = &(list->data[0]);
}

Iterator List_top_front(const List* list) {
	Iterator res = {list->head->next};
}

Iterator List_top_back(const List* list) {
	Iterator res = {list->head};
}

Iterator List_insert(List* list, Iterator* i, List_type t) {
	Iterator res = { list->top };
	if(!res.node) {
		return List_top_back(list);
	}
	list->top = list->top->next;
	res.node->data = t;
	res.node->next = i->node;
	res.node->prev = i->node->prev;
	res.node->prev->next = res.node;
	i->node->prev = res.node;
	list->size++;
	return res;
}

Iterator List_delete(List* list, Iterator* i) {
	Iterator res = List_top_back(list);
	if(it_List_equal(i,&res)) {
		return res;
	}
	res.node = i->node->next;
	res.node->prev = i->node->prev;
	i->node->prev->next = res.node;
	list->size--;
	//free array pnt
	i->node->next = list->top;
	list->top = i->node;
	i->node = 0;
	return res;
}

void List_destroy(List* list) {
	list->head = 0;
	list->size = 0;
	list->top = 0;
}

bool List_empty(const List* list) {
	Iterator fst = List_top_front(list);
	Iterator snd = List_top_back(list);
	return it_List_equal(&fst,&snd);
}

int List_Size(const List* list) {
	return list->size;
}


//elements functions
List_type element_List_by_num(const List* list, int num) {
	Iterator it,last;
	it = List_top_front(list);
	last =  List_top_back(list);
	while (num-1 > 0 && !it_List_equal(&it, &last)) {
		it_List_next(&it);
		num--;
	}
	return it_List_fetch(&it);
}

void element_List_store(const List* list, int num, List_type t) {
	Iterator it,last;
	it = List_top_front(list);
	last =  List_top_back(list);
	while (num-1 > 0 && !it_List_equal(&it, &last)) {
		it_List_next(&it);
		num--;
	}
	it_List_store(&it, t);
}

void List_insert_by_num(List* list, int num, List_type t) {
	Iterator it,last;
	it = List_top_front(list);
	last =  List_top_back(list);
	while (num-1 > 0 && !it_List_equal(&it, &last)) {
		it_List_next(&it);
		num--;
	}
	List_insert(list,&it,t);

}