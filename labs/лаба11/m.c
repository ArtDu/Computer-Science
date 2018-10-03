#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>


int main()
{
	setlocale(LC_ALL,"RUS");
	char c;
	int flaq = 0,eminus=0;
	int status=0,num=0;
	while(status!=-1)
    {
        c = getchar();
        if(c==EOF)
            return 0;

        switch(status)
        {
            case 0:
                if(c==' ' || c=='\t' || c=='\n' || c==',')
                {
                    status = 1;
                }
                putchar(c);
                break;
            case 1:
                if(c=='-')
                {
                    eminus = 1;
                }
                else if(isdigit(c))
                {

                    flaq = 1;
                    num = num*10 + c - '0';
                    //printf("\\%d\\",num);

                }
                else if(c=='C')
                {
                    status = 2;
                }
                else
                {
                    if(eminus==1)
                    {
                        printf("-");
                        eminus = 0;
                    }
                    if(flaq) {
                        printf("%d",num);
                        flaq = 0;
                    }
                    putchar(c);
                    num = 0;
                    status = 0;
                }
                break;
            case 2:
                if(c==' ' || c=='\t' || c=='\n' || c==',')
                {
                    if(eminus==1)
                    {
                        printf("%dF",(-num)+212);
                        eminus = 0;
                    }
                    else
                    {
                        printf("%dF",num+212);
                    }
                    putchar(c);
                    num = 0;
                    flaq = 0;
                    status = 1;
                }
                else
                {
                    if(eminus==1)
                    {
                        printf("-");
                        eminus = 0;
                    }
                    printf("%dC",num);
                    putchar(c);
                    num = 0;
                    flaq = 0;
                    status = 0;
                }
                break;

        }
    }
	return 0;
}
