/*  Автор: Дубинин Артем
    Группа М80-103Б
    Практикум по курсам "Основы информатики", "Алгоритмы и структуры данных"
    Задание 3. Вещестенный тип. Приближенные вычисления. Таблулирование функций*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL,"rus");
    const int width1 = 20;
    const int width2 = 30;
    const int width3 = 34;
    const int width4 = 5;
	const double a = 0.1;
	const double b = 0.6;
	const int k=1;
	double h;
	double eps = 1;
	double x = a;
	double TaylorValue;
	int n;
	printf("Enter n\n");
	scanf("%d", &n);
	h = (b - a) / n;

	while (eps / 2 + 1 != 1)
		eps /= 2;
	printf(
			"\nMachine epsilon of type double at System Compaq C at Digital alfa:\n");
	printf("%0.19lf\n\n", eps);
	printf(			"\tTable of value of Taylor's row and standart function f(x)=(x^2/4+x/2+1)*e^(x/2) \n");
	printf("|");
	for (int i = 0; i < width1; i++) {
		printf("-");
	}
	printf("-");
	for (int i = 0; i < width2; i++)
		printf("-");
	printf("-");
	for (int i = 0; i < width3; i++)
		printf("-");
	printf("-");
	for (int i = 0; i < width4; i++)
		printf("-");
	printf("|\n");
	printf("|");
	printf("%-*s", width1, " x");
	printf("|");
	printf("%-*s", width2, "Partial sum of the series");
	printf("|");
	printf("%-*s", width3, "Value of ");
	printf("|");
	printf("%-*s", width4, "Iter.");
	printf("|\n");
	printf("|");
	printf("%-*s", width1, "");
	printf("|");
	printf("%-*s", width2, " for (x^2/4+x/2+1)*e^(x/2)");
	printf("|");
	printf("%-*s", width3, "(x^2/4+x/2+1)*e^(x/2) function");
	printf("|");
	printf("%-*s", width4, "count");
	printf("|\n");
	printf("|");
	for (int i = 0; i < width1; i++)
		printf("-");
	printf("|");
	for (int i = 0; i < width2; i++)
		printf("-");
	printf("|");
	for (int i = 0; i < width3; i++)
		printf("-");
	printf("|");
	for (int i = 0; i < width4; i++)
		printf("-");
	printf("|\n");

	double summand;
	int factorial;
	double xpower;
	double m = 0;
	int mmm = 0;
	int tmmmm = 0;
	for (int i = 0; i < n + 1; i++) {
		summand = 1;
		xpower = 1;
		factorial = 1;
		tmmmm = 0;
		while (summand > eps*k) {
			TaylorValue += (summand);
			m += 1;
			xpower = xpower * (x/2);

			factorial *= m;
			mmm++;
			tmmmm++;
			//printf("fact=%d\n", factorial);
			//printf("\n ans=%d\n", ((m*m+1)/ factorial));
			summand = ((m*m+1) / factorial) * xpower;
			//printf("\%lf\n", summand);

		}
		printf("|");
		printf("%-*g", width1, x);
		printf("|");
		printf("%-.*lf", width2 - 2, TaylorValue);
		printf("|");
		printf("%-.*lf", width3 - 2, ((x*x)/4+x/2+1)*exp(x/2));
		printf("|");
		printf("%*d ", width4 - 1, tmmmm);
		printf("|\n");

		x += h;
		m = 0;
		TaylorValue = 0;
		factorial = 1;
	}

	printf("-");
	for (int i = 0; i < width1; i++)
		printf("-");
	printf("-");
	for (int i = 0; i < width2; i++)
		printf("-");
	printf("-");
	for (int i = 0; i < width3; i++)
		printf("-");
	printf("-");
	for (int i = 0; i < width4; i++)
		printf("-");
	printf("-\n");

	return 0;
}
