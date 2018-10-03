#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "table.h"
#define valCount 12

int main(int argc, char* argv[]) {
	//system("chcp 65001");

    Table_Element table[valCount];

	Table_Element lookingFor;

	char input = 'q';
	int working = 1;
    char table_name[100];
    int file_in = 0;


	do {
		printf("\nВведите команду (? - справка)\n");
		scanf(" %c", &input);
		switch (input) {
			case 't':
			    scanf("%s",table_name);

                if (initDictionary(table, valCount, argv[0], table_name)) {
                    printf("Не удалось считать таблицу\n");
                    file_in = 0;
                    break;
                }
                else {
                    printf("Таблица считана\n");
                    file_in = 1;
                }
                break;
			case 'p':
			    if(file_in) {
                    printDictionary(table, valCount);
                    printf("\n");
			    }
				else {
			        printf("Таблица не считана\n");
			    }
				break;
			case 's':
			    if (file_in) {
                    if (isSorted(table, valCount)) {
                        printf("Ошибка. Таблица уже отсортирована\n");
                    } else {
                        InsertSort(table, valCount);
                        printf("Таблица отсортирована\n");
                    }
                }
                else {
                    printf("Таблица не считана\n");
                }
				break;
			case 'r':
			    if(file_in) {
                    reverse(table,  valCount);
                }
                else {
                    printf("Таблица не считана\n");
                }
				break;
			case 'i':
			    if(file_in) {
                    scramble(table,  valCount);
                }
                else {
                    printf("Таблица не считана\n");
                }
				break;
			case 'f':
			    if(file_in) {
                    if (!isSorted(table, valCount))
                        printf("Ошибка. Таблица не отсортирована\n");
                    else {
                        printf("Введите ключ: ");
                        scanf("%s", &lookingFor.key);
                        int foundInd = binSearch(table, valCount+1, lookingFor);

                        if (foundInd > -1)
                            printf("Найдена строка: %s\n", table[foundInd].val);
                        else
                            printf("Строка с таким ключом не найдена\n");
                    }
			    }
                else {
                    printf("Таблица не считана\n");
                }

				break;


			case '?':
				printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
                    printf("t<название>    ввести таблицу\n");
					printf("p              печать\n");
					printf("s              сортировка\n");
					printf("r              реверс\n");
					printf("i              перемешать\n");
					printf("f              двоичный поиск\n");
					printf("?              справка\n");
					printf("q              выход\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			case 'q':
				working = 0;
				printf("Программа завершена\n");
				break;
			default:
				printf("Неизвестная команда\n");
				break;
		}
	} while (working);

	return 0;
}
