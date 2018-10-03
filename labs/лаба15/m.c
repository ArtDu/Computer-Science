#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>



int n,a[10][10],b[10],maxxEl=-2147483646;
int main()
{
	setlocale(LC_ALL,"Russian");   
    printf("Введите кол-во строк-столбцов:\n");
    while(scanf("%d",&n) != EOF) 
    {
        for(int k = 0; k<10; ++k)
                        b[k] = 0;   
        maxxEl=-2147483646;
        printf("Введите элементы:\n");
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                scanf("%d",&a[i][j]);
                if(a[i][j]>maxxEl)
                {
                    for(int k = 0; k<10; ++k)
                        b[k] = 0;
                    maxxEl = a[i][j];
                    b[j] = 1;
                }
                else if(a[i][j]==maxxEl)
                {
                    b[j] = 1;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(b[j]==0)
                {
                    printf("%d ", a[i][j]);
                }
            }
            printf("\n");
        }
        /*for(long long i = 0; i < 10; ++i) {
            printf("%d",b[i]);
        }*/
        printf("---------------------------------------\n");
        printf("Введите кол-во строк-столбцов:\n");
    }
    
	return 0;
}
