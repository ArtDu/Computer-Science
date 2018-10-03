#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <limits.h>



int main()
{
	setlocale(LC_ALL,"Russian");
	long long a,k;
	bool flaq = false;
	while(scanf("%lld",&a))
    {
        
        if(a>INT_MAX || a<INT_MIN) {
            printf("Ошибка переполнения\n");
        }
        else {
            flaq=false;
            if(a<0) {
                flaq = true;
                a = -a;
            }
            if(a!=0) {
                a = a%(int)floor(pow(10,(int)log10(a)));
                a /= 10;
            }
            printf("\t%lld\n",flaq ? -a : a);
        }
    }
	return 0;
}
