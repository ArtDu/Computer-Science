#include <stdio.h>
#include "tree.c"

//ВСЕ ВЕРШИНЫ ИМЕЮТ РАЗЛИЧНОЕ ЗНАЧЕНИЕ
//r 0 a 0 1 a 0 2 a 0 3 a 0 4 a 1 19 a 2 17 a 2 18 p
//r 0 a 0 1 a 0 2 a 0 3 a 0 4 a 1 19 a 2 17 a 2 18 a 18 20 a 20 13 a 13 99 a 99 77 a 99 33 a 33 12
//->(выбор по указателю) имеет приоритет выше, чем &(адрес) и *(разыменование) Ассоциативность <-----
int main(void) {
	int working = 1;
	char input = 0;
	int data1, data2 = 0;
	Node *root = NULL;
	Node* tmpNode = NULL;
	do {
		printf("\nВведите команду (? - справка)\n");
		scanf(" %c", &input);
		//Если в строке форматирования встретится разделитель, 
		//то функция scanf() пропустит один или несколько разделителей во входном потоке.
		switch (input) {
		case 'a':
			scanf(" %d %d", &data1, &data2);
			switch (addNode(&root, data1, data2)) {
			case 0:
				printf("%d стал сыном %d\n", data2, data1);
				break;
			case 1:
				printf("Такого родителя нет\n");
				break;
			case 2:
				printf("Дерево пусто\n");
				break;
			default:
				printf("Такой элемент уже есть\n");
				break;
			}

			break;
		case 'd':
			scanf(" %d", &data1);
			switch (removeNode(&root, data1)) {
			case 0:
				printf("Узел %d удален\n", data1);
				break;
			case 1:
				printf("Такого элемента не существует\n");
				break;
			default:
				printf("Дерево пусто\n");
				break;
			}
			break;
		case 'p':
			KLP(root, 0);
			break;
		case 'q':
			working = 0;
			break;
		case 'r':
			scanf(" %d", &data1);
			if (!isTreeEmpty(root))
				printf("Дерево не пусто\n");
			else {
				newNode(&root, data1);
				printf("Добавлен корень %d\n", data1);
			}
			break;
		case 't':
			if (!isTreeEmpty(root)) {
				if(!isTreeEmpty(root->son))
					data1 = treeMaxPow(root);
				else 
					data1 = 0;
				printf("Степень дерева %d\n", data1);
			} else
				printf("Дерево пусто\n");
			break;
		case '?':
			printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
			printf("r <число>       создать корень\n");
			printf("a <отец> <сын>  добавить узел\n");
			printf("d <число>       удалить узел\n");
			printf("p               распечатать дерево\n");
			printf("t               выполнить задание\n");
			printf("?               справка\n");
			printf("q               выход\n");
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

			break;
		default:
			printf("Неизвестная команда\n");
			break;
		}
	} while (working);

	destroyTree(&root);

	return 0;
}

