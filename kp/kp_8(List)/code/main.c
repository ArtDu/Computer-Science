#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "lis.h"

int main(void) {
	//a 9 13.4 1 0.75 2 1.3
	//ssystem("chcp 65001");
	char input = 'q';
	int working = 1;
	int pos;
	char val_1[100], val_2[100];
	Iterator it,last;
	List_type tmp_list_type;
	List a;


	List_create(&a);


	do {
		printf("Введите команду (? - справка)\n");
		scanf(" %c", &input);
		switch (input) {
		case '?':
		case 'h':
			printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
			printf("a <номер> <элемент>        добавить элемент\n");
			printf("d <номер>                  удалить элемент\n");
			printf("p                          вывести список\n");
            printf("l                          вывести длинну списка\n");
			//printf("e                          удалить список\n");
			printf("t <левая> <правая границы> выполнить задание\n");
			printf("?                          справка\n");
			printf("q                          выход\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			break;
		case 'a':
		

            scanf("%d", &(pos));
            if(pos==1)pos=1; 
			else if(pos%a.size==1)pos=a.size+1; 
			else if(pos%a.size==0)pos=a.size; 
			else pos%=a.size; 

            scanf("%s", tmp_list_type.lt);


            it = List_top_front(&a);
            last =  List_top_back(&a);
            while (pos-1 > 0 && !it_List_equal(&it, &last)) {
                it_List_next(&it);
                pos--;
            }
            //если ушло в терминальный, т.е больше списка, то элемент станет последним

            List_insert(&a, &it, tmp_list_type);

			break;
        case 'l':
            printf("%d\n", List_Size(&a));
            break;
        case 'd':
            if (List_empty(&a)) {
                printf("Список пуст\n");
                break;
            }
            scanf("%d", &(pos));
            if(pos >a.size && a.size!=0) {
                if(pos%a.size == 0)
                    pos = a.size;
                else
                    pos = pos%(a.size);
            }
            it = List_top_front(&a);
            last =  List_top_back(&a);
            while (pos-1 > 0 && !it_List_equal(&it, &last)) {
                it_List_next(&it);
                pos--;
            }
            if (it_List_equal(&it, &last))
                it_List_prev(&it);
            //если ушло в терминальный, т.е то будет удален последний
            List_delete(&a, &it);
            break;

		case 'p':
			if (!List_empty(&a)) {
				List_print(&a);
				printf("\n");
			} else {
				printf("Список пуст\n");
			}
			break;
		/*case 'e':
			List_destroy(&a);
			List_create(&a);
			break;*/
		case 't':
			if (!List_empty(&a)) {

                scanf("%s", val_1);
                scanf("%s", val_2);
                List_task(&a, val_1, val_2);
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
