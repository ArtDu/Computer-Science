#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <limits.h>



int n, a[8][8];
int main()
{
	setlocale(LC_ALL,"Russian");
    
    printf("Введите кол-во строк-столбцов\n");
    scanf("%d",&n);
    if(n==0)
        return 0 ;
    printf("Введите элементы\n");
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d",&a[i][j]);
        }
    }


    int i = 0, j = 0;

    if(n==1) {
        printf("%d\n", a[0][0]);
        return 0;
    }
    while(1)  
    {
        if(i==n-1 || j==n-1)
        {
            printf("%d ", a[i][j]);
            break;
        }
        
        if(i==0)
        {
            printf("%d ", a[i][j]);
            j++;
            while(j)
            {
                printf("%d ", a[i][j]);
                j--;
                i++;
            }
        }
        else {
            printf("%d ", a[i][j]);
            i++;
            while(i)
            {
                printf("%d ", a[i][j]);
                i--;
                j++;
            }
        }
    }

    //printf("%d %d\n", i, j);
    if(j>i) {
        i++;
    }
    else {
        j++;
    }
    while(1)
    {
        if(i==n-1 && j==n-1)
        {       
            printf("%d ", a[i][j]);
            break;
        }
        
        if(j+1==n) {
            while(i<n-1)
            {
                printf("%d ", a[i][j]);
                i++;
                j--; 
            }
            printf("%d ", a[i][j]);
            ++j;
        }
        else {
            while(j<n-1)
            {
                printf("%d ", a[i][j]);
                j++;
                i--; 
            }
            printf("%d ", a[i][j]);
            ++i;
        }
    }
    printf("\n");
	return 0;
}
