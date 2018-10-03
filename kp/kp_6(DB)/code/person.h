#ifndef __person_h__
#define __person_h__

typedef struct 
{
	char name[30]; //{Surname} size = 32
	
	char inits[5]; //{SurnameNamePatname} size = 5
	
	int things_count;// {0-2147483647}  size = 12
	int things_weight; //in killograms {0-2147483647} size = 12
	char to[35]; //{city/country}  size = 37
	
	char time[6]; //format {hh:mm} hh = {00-23} mm = {00-59}  size = 8
	
	int check_add_trans; //check of additional transfers = y/n {0} or {1}  size = 3
	int check_children; //check childrens = y/n {0} or {1}  size = 3

} person;

#endif // __person_h__



