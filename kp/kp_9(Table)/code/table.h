/*
 * table.h
 *
 *  Created on: May 29, 2017
 *      Author: mint
 */

#ifndef TABLE_H_
#define TABLE_H_
typedef struct _key{
	//int link;
	char key[10];
	char val[100];
}Table_Element;

/*
 * dependencies functions
 */
void swapRows(Table_Element table[],const int a, const int b);
int Compare(const char k1[10], const char k2[10]);
int cmp(const char k1[10], const char k2[10]);
int isEqualKeys(const char k1[10], const char k2[10]);


//init
int initDictionary(Table_Element table[], const int size, char dirName[1000], char fileName[100]);
//print
void printDictionary(Table_Element table[], const int size);
//sort
void InsertSort(Table_Element table[], const int size);
//reverse
void reverse(Table_Element table[], const int size);
//isSorted
int isSorted(const Table_Element table[], const int size);
//shuffle
void scramble(Table_Element table[], const int size);
//binSearch
int binSearch(const Table_Element table[],  const int size, const Table_Element target);


#endif /* TABLE_H_ */
