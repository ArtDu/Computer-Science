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

	list->head = malloc(sizeof(Item));
	list->head->next = list->head->prev = list->head;
	list->size = 0;
}

Iterator List_top_front(const List* list) {
	Iterator res = {list->head->next};
    return res;
}

Iterator List_top_back(const List* list) {
	Iterator res = {list->head};
	return res;
}

Iterator List_insert(List* list, Iterator* i, List_type t) {
	Iterator res = { malloc(sizeof(Item)) };
	if(!res.node) {
		return List_top_back(list);
	}

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
	free(i->node);
	i->node = 0;
	return res;
}

/*void List_destroy(List* list) {
	Item* i = list->head->next;
	while(i != list->head) {
	    Item* pi = list->head;
	    i = i->next;
	    free(pi);
	}
	free(list->head);
	list->head = 0;
	list->size = 0;
}*/

bool List_empty(const List* list) {
	Iterator fst = List_top_front(list);
	Iterator snd = List_top_back(list);
	return it_List_equal(&fst,&snd);
}

int List_Size(const List* list) {
	return list->size;
}



//not standart functions
void List_print(List *list) {

	List_type tmp_list_type;
	Iterator it, last = List_top_back(list);
	printf("Index:\t");
    for (int i = 1; i <= List_Size(list); ++i) {
        printf("%d ", i);
    }
	printf("\nArray:\t");
	for (it = List_top_front(list); !it_List_equal(&it,&last) ;  it_List_next(&it)) {

		tmp_list_type = it_List_fetch(&it);

		printf("%s ", tmp_list_type.lt);


	}

}

void List_task(List* list, char lbord[100], char rbord[100]) {
    List_type tmp_list_type;
    Iterator it, last = List_top_back(list);
    for (it = List_top_front(list); !it_List_equal(&it,&last) ;  ) {


        tmp_list_type = it_List_fetch(&it);
        if( strcmp(lbord,tmp_list_type.lt)<=0 && strcmp(rbord,tmp_list_type.lt)>=0) {

            it = List_delete(list, &it);
        }
        else {
            it_List_next(&it);
        }


    }
}


