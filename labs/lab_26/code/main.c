#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lis.h"

/*
Not standart functions
*/
void List_print(List *list);
void List_task_insert(List* list, List_type t);
void List_sort(List* list);


int main(void) {
	//a 9 13.4 1 0.75 2 1.3
	//system("chcp 65001");
	char input = 'q';
	int working = 1;
	int sorted = 0;
	List_type tmp_list_type;
	List a;
	Iterator it,last;
	int pos;

	List_create(&a);


	do {
		printf("Введите команду (? - справка)\n");
		scanf(" %c", &input);
		switch (input) {
		case '?':
		case 'h':
			printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
			printf("a <номер> <элемент>   добавить элемент\n");
			printf("d <номер>		      удалить элемент\n");
			printf("p  					  вывести список\n");
			printf("t  					  выполнить сортировку\n");
			printf("?  					  справка\n");
			printf("q  					  выход\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			break;
		case 'a':
			if(POOL_SIZE <= List_Size(&a)) {
				printf("Список переполнен\n");
				break;
			}
			//считывание зависит от Item
			printf("Введите номер\n");
			scanf("%d", &(pos));
			if(pos-1>a.size) {
				printf("Номер не верный!");
				break;
            }
			printf("Введите <ключ><значение>\n");
			scanf("%d", &(tmp_list_type.key));
			scanf("%f", &(tmp_list_type.value));
			
            it = List_top_front(&a);
            last =  List_top_back(&a);
            while (pos-1 > 0 && !it_List_equal(&it, &last)) {
                it_List_next(&it);
                pos--;
            }
            //если ушло в терминальный, т.е больше списка, то элемент станет последним

            List_insert(&a, &it, tmp_list_type);

			break;
		case 'p':
			if (!List_empty(&a)) {
				List_print(&a);
				printf("\n");
			} else {
				printf("Список пуст\n");
			}
			break;
		case 'd':
			if (!List_empty(&a)) {
				printf("Введите номер\n");
				scanf("%d", &(pos));
				if(pos>a.size) {
					printf("Номер не верный!");
					break;
	            }

	            it = List_top_front(&a);
	            last =  List_top_back(&a);
	            while (pos-1 > 0 && !it_List_equal(&it, &last)) {
	                it_List_next(&it);
	                pos--;
	            }
	            //если ушло в терминальный, т.е больше списка, то элемент станет последним

				List_delete(&a, &it);
				printf("Элемент удален\n");
				
			} else {
				printf("Список пуст\n");
			}
			
			break;
		case 't':
			if (!List_empty(&a)) {
				List_sort(&a);
				printf("Сортировка списка вставкой выполнена!\n");
				//deque_destroy(a);
			} else {
				printf("Список пуст\n");
			}
			break;

		
		case 'q':
			/*dequeDestroy(&a);*/
			printf("Программа завершена\n");
			working = 0;
			break;
		default:
			printf("Неизвестная команда\n");
			break;

		}
	} while (working);

	return 0;
}


//not standart functions
void List_print(List *list) {

	List_type tmp_list_type;
	int i;
	Iterator it, last = List_top_back(list);
	printf("Номер\tКлюч\tЗначение\n");
	for (i = 1, it = List_top_front(list); !it_List_equal(&it,&last) ;  it_List_next(&it), i++) {

		tmp_list_type = it_List_fetch(&it);

		printf("%d\t%d\t%.2f\n", i, tmp_list_type.key, tmp_list_type.value);


	}

}

void List_sort(List* list) {

	List_type tmp_i,tmp_j,
			min_list_type;

	List tmp_list;
	List_create(&tmp_list);



	for (int i = 1; i <= List_Size(list) ; ++i) {
		tmp_i = element_List_by_num(list, i);
		List_task_insert(&tmp_list, tmp_i);
	}
	for (int i = 1; i <= List_Size(&tmp_list) ; ++i) {
		tmp_i = element_List_by_num(&tmp_list, i);
		element_List_store(list, i, tmp_i);
	}

	/*Iterator it_i, it_j, last = List_top_back(list);
	for (it_i = List_top_front(list), it_j = List_top_front(&tmp_list); !it_List_equal(&it_i,&last) ;
			it_List_next(&it_i), it_List_next(&it_j)) {
		tmp_j = it_List_fetch(&it_j);
		it_List_store(&it_i, tmp_j);
	}*/


}

void List_task_insert(List* list, List_type t) {
	int flaq = 1;
	List_type tmp_list_type;

	for (int i = 1; i <= List_Size(list) ; ++i) {
		tmp_list_type = element_List_by_num(list, i);
		if(tmp_list_type.key >= t.key) {
			List_insert_by_num(list, i, t);

			flaq = 0;
			break;
		}
	}

	if(flaq == 1) {
		int size_ = List_Size(list);
		List_insert_by_num(list, size_, t);
	}
}
