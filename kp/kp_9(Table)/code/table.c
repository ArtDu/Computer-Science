#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//#include <direct.h>
#include "table.h"

/*
 * additional functions
*/
int randomAB(const int a, const int b) {
    return a + rand() % (b - a + 1);
}
void swap(Table_Element a[],int i,int j){
    Table_Element k;
    strcpy(k.key,a[i].key);
    strcpy(k.val,a[i].val);
    //k.link = a[i].link;

    a[i] = a[j];
    a[j] = k;

}
/*
 * additional functions(table.h)
*/
void swapRows(Table_Element table[], const int a, const int b) {
    Table_Element tmp_el;
    tmp_el = table[a];
    table[a] = table[b];
    table[b] = tmp_el;
}
int Compare(const char k1[10], const char k2[10]) {
    //возращает 1 если ключ 1 строго больше  2
    if ( (strcmp(k1,k2)>=0) )
        return 1;
    return 0;

}
int cmp(const char k1[10], const char k2[10]) {
    if ( (strcmp(k1,k2)>=0) )
        return 1;
    return 0;
}
int isEqualKeys(const char k1[10], const char k2[10]) {
    return (strcmp(k1,k2)==0) && strlen(k1)==strlen(k2);
}

//init
void getRow(FILE *stream, char *str, const int size) {
	int cnt = 0, ch;

	while ((ch = getc(stream)) != '\n' && cnt < size - 1)
		str[cnt++] = ch;

	str[cnt] = '\0';
}
int initDictionary(Table_Element table[], const int size, char dirName[1000], char fileName[100]) {

    char final_dir_name[1000];
    final_dir_name[0]='\0';

    for (int j = strlen(dirName)-1; j >= 0 ; --j) {
        if(dirName[j]=='/')
        {
            strncat(final_dir_name,dirName,j+1);
            break;
        }
    }
    strcat(final_dir_name,fileName);
    //printf("%s\n", final_dir_name);

    FILE *file;
    file = fopen(final_dir_name, "r");
	if (file == NULL)
		return -1;

	int i = 0;
	while (i < size && fscanf(file, " %s ", &table[i].key) == 1) {

		//table[i].link=i;
		getRow(file, table[i].val, sizeof(table[i].val));
		i++;
	}
	fclose(file);
	return 0;
}

//print
void printDictionary(Table_Element table[], const int size) { //t input p
    printf(" ");
    for(long long i = 0; i < 45; ++i) {
        printf("—");
    }
    printf("\n");
    printf("| keys |                  Values              |\n");
    printf(" ");
    for(long long i = 0; i < 45; ++i) {
        printf("—");
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("|%6s| %37s|\n", table[i].key, table[i].val);
    }
    printf(" ");
    for(long long i = 0; i < 45; ++i) {
        printf("—");
    }
}

//insert
void InsertSort(Table_Element table[], const int size) {

    for (int i=0; i<size; ++i){
        char temp[10];
        strcpy(temp,table[i].key);
        int left=0;
        int right=i;
        while (left<right){
            int middle=(left+right)/2;
            if  (strcmp(temp,table[middle].key)>=0)
                left=middle+1;
            else
                right=middle;
        }
        for (int j=i;j>left;--j){
            swap(table,j-1,j);
        }
    }

}

//reverse
void reverse(Table_Element table[],  const int size) {
    int i, j;

    for (i = 0, j = size - 1; i < j; i++, j--)
        swapRows(table,  i, j);
}

//isSorted
int isSorted(const Table_Element table[], const int size) {
    for (int i = 0; i < size - 1; i++)
        if (!(Compare(table[i + 1].key, table[i].key) ))
            return 0;
    return 1;
}

//Shuffle
void scramble(Table_Element table[], const int size) {
    for (int z = 0; z < size; z++)
        swapRows(table,  randomAB(0, size - 1), z);

}

//binSearch
int binSearch(const Table_Element table[],  const int size, const Table_Element target) {
    int L = 0;
    int R = size - 1;
    int mid;
    while (L < R) {
        mid = (R + L) / 2;
        if (isEqualKeys(table[mid].key, target.key))
            return mid;
        else if (cmp(target.key, table[mid].key))
            L = mid + 1;
        else
            R = mid;
    }

    if (isEqualKeys(table[mid].key, target.key))
        return R;

    return -1;
}


