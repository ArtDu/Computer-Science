#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "person.h"

void wout_fname()
{
	printf("Usage: program filename.\n");
}

void fnot_exst()
{
	printf("File not exist.\nUsage: program filename.\n");
}

int read_db(FILE* f_in, FILE* f_out)
{
	person tmp;
	int count=0;
	// tmp.name = (char*)malloc(50);
	// tmp.inits = (char*)malloc(50);
	// tmp.to = (char*)malloc(100);
	// tmp.time = (char*)malloc(10);
	
	while (8 == fscanf(f_in,"%[^ ] %[^ ] %d %d %[^ ] %[^ ] %d %d",tmp.name,tmp.inits,&tmp.things_count,&tmp.things_weight
			,tmp.to,tmp.time,&tmp.check_add_trans,&tmp.check_children))
	{
		fwrite(&tmp,sizeof(tmp),1,f_out);
		count++;
	}
	
	return count;
}

int main(int argc, char* argv[])
{
	if(argc<3) {
		wout_fname();
		return 1;
	}

	
	FILE* f_in  = fopen(argv[1],"r");

	if(!f_in) {
		fnot_exst();
		return 2;
	}


	char* db_name_pfix = "";
	char* final_db_name = strcat(argv[2], db_name_pfix);
	FILE* f_out = fopen(final_db_name,"w");

	int count = read_db(f_in,f_out);
	if(count>0) {
		printf("Success.\nCount of row in db = %d.\n", count);
	}
	else {
		printf("Empty file\n");
		wout_fname();
	}
	fclose(f_in);
	fclose(f_out);
	return 0;
}
