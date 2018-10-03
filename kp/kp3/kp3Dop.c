#include <stdio.h>
#include <locale.h>
int main() {
	
setlocale(LC_ALL,"Rus");
float epsf=1;
double epsd=1;
long double epsld=1;

while (epsf / 2 + 1 != 1)
		epsf /= 2;
while (epsd / 2 + 1 != 1)
		epsd /= 2;
while (epsld / 2 + 1 != 1)
		epsld /= 2;
printf("Машинное эпсилон для вещественных типов в системе Compaq C на Digital Alpha\n");
printf("\nfloat\t\t%.25f\ndouble\t\t%.25lf\nlong double\t%.25Lf",epsf,epsd,epsld);
printf("\n\nЭкспоненциальная форма\n");
printf("float\t\t%e\ndouble\t\t%le\nlong double\t%Le\n",epsf,epsd,epsld);

double ex=1;
double ex1=0;
while(ex1<ex){
	ex=ex1;
	ex1--;
}
printf("%lf",ex);
}

