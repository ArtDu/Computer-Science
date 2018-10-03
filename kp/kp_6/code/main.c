#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "person.h"
#include <stdlib.h> 

#define TABLE_WIDTH 103
#define TABLE_NAME_WIDTH 20
#define TABLE_INITS_WIDTH 5
#define TABLE_THINGS_COUNT_WIDTH 15
#define TABLE_THINGS_WEIGHT_WIDTH 15
#define TABLE_TO_WIDTH 25
#define TABLE_TIME_WIDTH 8
#define TABLE_CHECK_WIDTH 3

void without_filename() //error 'without file name'
{
	printf("Error.\nUsage: [-f] [-p][INT] FILE.\n");
}

void file_not_exist(char* file) //file not exist
{
	printf("File \"%s\" not exist.\nUsage: [-f] [-p][INT] FILE.\n",file);
}

//////////////PRINT TABLE/////////////////////////


void print_bottom_row()
{
	printf("|");
	for(int i = 0; i < TABLE_NAME_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_INITS_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_THINGS_COUNT_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_THINGS_WEIGHT_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_TO_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_TIME_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_CHECK_WIDTH; ++i) {
		printf("_");
	}
	printf("|");
	for(int i = 0; i < TABLE_CHECK_WIDTH; ++i) {
		printf("_");
	}
	printf("|\n");
}

void print_top_row()
{
	printf("D* - direct fly {1=yes,0=no}\n");
	printf("C* - children {1=yes,0=no}\n");
	for(int i = 0; i < TABLE_WIDTH; ++i) {
		printf("_");
	}
	printf("\n");

	printf("|Surname             ");
	printf("|Inits");
	printf("|Count Baggage  ");
	printf("|Weight Baggage ");
	printf("|city/country             ");
	printf("|time    ");
	printf("|D* ");
	printf("|C* |");

	printf("\n");
	print_bottom_row();
}

void print_row(person p)
{
	if(p.name[0] == '\n') {
		p.name[0] = '|';
		printf("%-21s", p.name);
	}
	else {
		printf("|%-20s", p.name);
	}
	 
	
	printf("|%-5s", p.inits);
	printf("|%-15d", p.things_count);
	printf("|%-15d", p.things_weight);
	printf("|%-25s", p.to);
	printf("|%-8s", p.time);
	printf("|%-3d", p.check_add_trans);
	printf("|%-3d|\n", p.check_children);

	print_bottom_row();

}

void print_table(person p[],int count)
{
	print_top_row();

	for(long long i = 0; i < count; ++i) {
		print_row(p[i]);
	}
	printf("\n");
}
/////////////////////////////////////////////////////

void check_task(person p[],int count, int p_diff) {
	for(long long i = 0; i < count; ++i) {
		for (long long j = i+1; j < count; ++j)
		{
			if(p[i].things_count == p[j].things_count)
			{
				if(abs(p[i].things_weight - p[j].things_weight)<=p_diff)
				{
					printf("Yes, table have.\n\n");
					printf("Difference of 2 record  <= -p\n");
					printf("%d <= %d\n", abs(p[i].things_weight - p[j].things_weight),p_diff);
					print_top_row();
					print_row(p[i]);
					print_row(p[j]);
					printf("\n");

					return;
				}
			}
		}
	}
	printf("NO, table have not.\n\n");
}


int main(int argc, char* argv[])
{
	if(argc<3) { //if even 1 key name and filename exist
		without_filename();
		return 1;
	}

	int check_f=0,check_p=0;
	int count_p;
	
	FILE* f_in;
	f_in = 0;
	for(int i=1; i<argc; ++i) { //choose arguments and filename

		if (!strcmp(argv[i],"-f")) {
			check_f = 1;
		}
		else if(!strcmp(argv[i],"-p")) {
			check_p = 1;
			if(i+1==argc) {
				without_filename();
			}
			i++;
			count_p = atoi (argv[i]);
			if(count_p == 0) {
				if(argv[i][0] != '0' || strlen(argv[i]) != 1) {
					without_filename();
					return 1;
				}
			}

	
		}
		else {
			f_in  = fopen(argv[i],"r");
			if(!f_in) {
				file_not_exist(argv[i]);
				return 2;
			}
		}
	
	}

	
	if(!f_in || !( check_f || check_p)) { //if keys wrong or file not exist
		without_filename();
		return 2;
	}

	fseek(f_in,0,SEEK_END); 
	int fsize = ftell(f_in); //file size
	fseek(f_in,0,SEEK_SET);

	person tmp_p; 
	int psize = sizeof(tmp_p); //person struct size
	int count_of_recs = fsize/psize; //count of records of table
	
	person p[count_of_recs+2]; //from binary to massif
	int j = 0;
	while(fread(&p[j],sizeof(p),1,f_in) == 1) {
		++j;
	}


	if(check_p) {
		check_task(p,count_of_recs,count_p);
	}

	if(check_f) { //-f print table
		
		print_table(p,count_of_recs);
			
	}

	return 0;
}