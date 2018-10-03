#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct matrix_array
{
	int column;
	float val;
};


int readMatrix(struct matrix_array A[], int* AINDEX, int* width, int* heigth) {
	//CONSIDER THAT all of THIS PARAMETERS WILL be rewritten
	float element = 0;			//current element
	*AINDEX = 0;	        //current A array index

							/*printf("%d\n", *AINDEX);
							return 0;*/
	int elementsReadCOUNT = 0;	//elements read equals current column
	printf("Enter matrix heigth\n");
	scanf("%d", heigth);
	if (*heigth < 1) {
		printf("Wrong heigth value: %d", *heigth);
		return 1;
	}

	printf("Enter matrix width\n");
	scanf("%d", width);
	if (*width < 1) {
		printf("Wrong width value: %d", *width);
		return 1;
	}

	printf("Enter matrix\n");
	A[*AINDEX].column = 0;
	A[*AINDEX].val = 1;
	*AINDEX = *AINDEX + 1;
	for (int i = 1; i <= *heigth; i++) {
		for (int j = 1; j <= *width; j++) {
			scanf(" %f", &element);
			//non zero element
			if (element != 0) {
				A[*AINDEX].column = j;
				A[*AINDEX].val = element;
				elementsReadCOUNT++;
				*AINDEX = *AINDEX + 1;
			}

		}
		if (i != *heigth) {
			A[*AINDEX].column = 0;
			A[*AINDEX].val = i + 1;
			*AINDEX = *AINDEX + 1;
		}
		else {
			A[*AINDEX].column = 0;
			A[*AINDEX].val = 0;
			*AINDEX = *AINDEX + 1;
		}
	}

	/*for (int i = 0; i < *AINDEX; ++i)
	{
	if(A[i].column == 0)
	printf("(%d,%d)\n", A[i].column, (int) A[i].val);
	else
	printf("(%d,%f)\n", A[i].column,A[i].val);
	}*/
	return 0;
}

void writeInnerRepresentation(struct matrix_array A[], int* AINDEX, int* width, int* heigth) {
	//WILL NOT REWRITE ANY PARAMETERS
	//newline represended by -1 in any array
	//-1 in M means full zero stroke
	//-1 in A means end of current stroke
	printf("Array V:\t");
	for (int i = 0; i < *AINDEX; ++i)
	{
		if (A[i].column == 0)
			printf("%d %d ", A[i].column, (int)A[i].val);
		else
			printf("%d %.1f ", A[i].column, A[i].val);
	}
	printf("\n");
}

void writeStandartRepresentation(struct matrix_array A[], int* ALEN, int width, int heigth) {
	//WILL NOT REWRITE ANY PARAMETERS
	int 	AINDEX = 1;
	int currentRow = 1;
	for (int i = 0; i < heigth; i++) {
		for (int k = 0; k < width; ++k)
		{
			if (i + 1 == A[AINDEX].val && A[AINDEX].column == 0)
				AINDEX++;
			if (A[AINDEX].column == 0) {

				while (k < width)
				{
					printf("      0");
					k++;
				}
				AINDEX = AINDEX + 1;
			}
			else if (A[AINDEX].column == k + 1) {
				printf("      %.1f", A[AINDEX].val);
				AINDEX = AINDEX + 1;
			}
			else {
				printf("      0");
			}

		}
		printf("\n");
	}
}

void clearArr(struct matrix_array A[], int len) {
	for (int i = 0; i < len; i++) {
		A[i].column = 0;
		A[i].val = 0;
	}
}

int sumMatrix(
    struct matrix_array fst_matr[], int* fst_len, int* fst_width, int* fst_heigth,   //first matrix
    struct matrix_array snd_matr[], int* snd_len, int* snd_width, int* snd_heigth,   //second matrix
    struct matrix_array trd_matr[], int* trd_len, int* trd_width, int* trd_heigth) { //sum_matrix
	//CONSIDER THAT all of THIS PARAMETERS WILL be rewritten


	float s_arr[*fst_heigth+5][*fst_width+5];
	for(long long i = 0; i < *fst_heigth+5; ++i) {
		for (int j = 0; j < *fst_width+5; ++j)
		{
			s_arr[i][j] = 0;
		}
	}

	int cur_row = 0;
	for (int i = 0; i < *fst_len; i++) {
		if(fst_matr[i].column!=0)
        {
            s_arr[cur_row][fst_matr[i].column] += fst_matr[i].val;
        }
        else{
		    cur_row++;
		}
	}
    cur_row = 0;
    for (int i = 0; i < *snd_len; i++) {
        if(snd_matr[i].column!=0)
        {
            s_arr[cur_row][snd_matr[i].column] += snd_matr[i].val;
        }
        else{
            cur_row++;
        }
    }


	int flaq = 1;
	for(long long i = 1; i <= *fst_heigth; ++i) {
		for (int j = 1; j <= *fst_width; ++j)
		{
			if(s_arr[i][j] != s_arr[j][i])
				flaq = 0;
			printf("%f ", s_arr[i][j]);
			
		}
		printf("\n");
	}
	if(flaq && *fst_width == *fst_heigth)
	{
		printf("Матрица симметрична\n");
	}
	else{
		printf("Матрица не симметрична\n");
	}
	return 0;
}



int main(void) {
	
	
	
	struct matrix_array tmp_arr[500]; //array matrix
	int tmp_arrlen = 500; 		//length of array matrix
	int tmp_height = 0;
	int tmp_width = 0;

	//1
	struct matrix_array arr_1[500]; //array matrix 
	int arrlen_1 = 500; 		//length of array matrix
	int width_1 = 0; 			//width matrix
	int height_1 = 0; 		//height matrix
	int matrixEmpty_1 = 1;

	//2
	struct matrix_array arr_2[500]; //array matrix
	int arrlen_2 = 500; 		//length of array matrix
	int width_2 = 0; 			//width matrix
	int height_2 = 0; 		//height matrix
	int matrixEmpty_2 = 1;

	int working = 1;
	char input,matrix_num;
	do {
		printf("\nВведите команду (? - справка)\n");
		scanf(" %c", &input);
		switch (input) {
		case 'a':
			scanf(" %c", &matrix_num);
			switch (matrix_num) {
				case '1':
					if (!matrixEmpty_1)
						printf("Текущая матрица будет перезаписана\n");
					matrixEmpty_1 = 0;
					clearArr(arr_1, arrlen_1);
					if (readMatrix(arr_1, &arrlen_1, &width_1, &height_1)) {//consider that parameters will change
						printf("Считывание не удалось");
						clearArr(arr_1, arrlen_1);
						matrixEmpty_1 = 1;
					}		//reading failed
					printf("\n");

					break;
				case '2':
					if (!matrixEmpty_2)
						printf("Текущая матрица будет перезаписана\n");
					matrixEmpty_2 = 0;
					clearArr(arr_2, arrlen_2);
					if (readMatrix(arr_2, &arrlen_2, &width_2, &height_2)) {//consider that parameters will change
						printf("Считывание не удалось");
						clearArr(arr_2, arrlen_2);
						matrixEmpty_2 = 1;
					}		//reading failed
					printf("\n");

					break;
				default:
				    printf("Номер матрицы неверный\n");
			}
			
			break;

        case 'd':
            scanf(" %c", &matrix_num);
            switch (matrix_num) {
                case '1':
                    if (matrixEmpty_1)
                        printf("Матрица пуста\n");
                    else {
                        clearArr(arr_1, arrlen_1);
                        matrixEmpty_1 = 1;
                        printf("Матрица удалена\n");
                    }
                    break;
                case '2':
                    if (matrixEmpty_2)
                        printf("Матрица пуста\n");
                    else {
                        clearArr(arr_2, arrlen_2);
                        matrixEmpty_2 = 1;
                        printf("Матрица удалена\n");
                    }
                    break;
                default:
                    printf("Номер матрицы неверный\n");
            }
            break;
        case 'i':
            scanf(" %c", &matrix_num);
            switch (matrix_num) {
                case '1':
                    printf("Внутреннее представление\n");
                    if (matrixEmpty_1)
                        printf("Матрица пуста\n");
                    else
                        writeInnerRepresentation(arr_1, &arrlen_1, &width_1, &height_1);

                    break;
                case '2':
                    printf("Внутреннее представление\n");
                    if (matrixEmpty_2)
                        printf("Матрица пуста\n");
                    else
                        writeInnerRepresentation(arr_2, &arrlen_2, &width_2, &height_2);
                    break;
                default:
                    printf("Номер матрицы неверный\n");
            }
            break;

        case 'p':
            scanf(" %c", &matrix_num);
            switch (matrix_num) {
                case '1':
                    printf("Cтандартное представление\n");
                    if (matrixEmpty_1)
                        printf("Матрица пуста\n");
                    else
                        writeStandartRepresentation(arr_1, &arrlen_1, width_1, height_1);
                    break;
                case '2':
                    printf("Cтандартное представление\n");
                    if (matrixEmpty_2)
                        printf("Матрица пуста\n");
                    else
                        writeStandartRepresentation(arr_2, &arrlen_2, width_2, height_2);
                    break;
                default:
                    printf("Номер матрицы неверный\n");
            }
            break;

        case 't':
            if (matrixEmpty_1)
                printf("Матрица 1 пуста\n");
            else if (matrixEmpty_2)
                printf("Матрица 2 пуста\n");
            else if(width_1==width_2 && height_1==height_2) {
                clearArr(tmp_arr, tmp_arrlen);
                sumMatrix(
                        arr_1, &arrlen_1, &width_1, &height_1,
                        arr_2, &arrlen_2, &width_2, &height_2,
                        tmp_arr, &tmp_arrlen, &tmp_width, &tmp_height
                );
            }
            else{
                printf("Разные размеры матриц!");
            }
            break;

		case '?':
			printf("~~~~~~~~~~~Список команд~~~~~~~~~~~\n");
			printf("a <номер матрицы(1 или 2)>   ввести матрицу\n");
			printf("d <номер матрицы(1 или 2)>   удалить матрицу\n");
			printf("p <номер матрицы(1 или 2)>   вывести матрицу в стандартном представлении\n");
			printf("i <номер матрицы(1 или 2)>   вывести матрицу во внутреннем представлении\n");
			printf("t                            выполнить задание\n");
			printf("?                            справка\n");
			printf("q                            выход\n");
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
