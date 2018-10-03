/*  Автор: Лукашкин Константин
    Группа М80-104Б
    Практикум по курсам "Основы информатики", "Алгоритмы и структуры данных"
    Задание 3. Вещестенный тип. Приближенные вычисления. Таблулирование функций*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL,"Rus");
    const int width1 = 20;
    const int width2 = 25;
    const int width3 = 25;
    const int width4 = 5;
	const double a = 0;
	const double b = 1.0;
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
	printf(			"\tTable of value of Taylor's row and standart function f(x)=sin x\n");
	printf("┏");
	for (int i = 0; i < width1; i++)
		printf("━");
	printf("┯");
	for (int i = 0; i < width2; i++)
		printf("━");
	printf("┯");
	for (int i = 0; i < width3; i++)
		printf("━");
	printf("┯");
	for (int i = 0; i < width4; i++)
		printf("━");
	printf("┓\n");
	printf("┃");
	printf("%-*s", width1, " x");
	printf("│");
	printf("%-*s", width2, "Partial sum of the series");
	printf("│");
	printf("%-*s", width3, "Value of sin x function");
	printf("│");
	printf("%-*s", width4, "Iter.");
	printf("┃\n");
	printf("┃");
	printf("%-*s", width1, "");
	printf("│");
	printf("%-*s", width2, " for sin x");
	printf("│");
	printf("%-*s", width3, "");
	printf("│");
	printf("%-*s", width4, "count");
	printf("┃\n");
	printf("┠");
	for (int i = 0; i < width1; i++)
		printf("─");
	printf("┼");
	for (int i = 0; i < width2; i++)
		printf("─");
	printf("┼");
	for (int i = 0; i < width3; i++)
		printf("─");
	printf("┼");
	for (int i = 0; i < width4; i++)
		printf("─");
	printf("┨\n");

	double summand;
	int sign = 1;
	int factorial;
	double xpower;
	int m = 1;
	for (int i = 0; i < n + 1; i++) {
		summand = x;
		xpower = x;
		while (summand > eps*k) {
			TaylorValue += (summand * sign);
			sign = -sign;
			m += 2;
			xpower = xpower * x * x;
			factorial *= (m - 1) * m;
			summand = xpower / factorial;

		}
		printf("┃");
		printf("%-*g", width1, x);
		printf("│");
		printf("%-.*lf", width2 - 2, TaylorValue);
		printf("│");
		printf("%-.*lf", width3 - 2, sin(x));
		printf("│");
		printf("%*d ", width4 - 1, (m - 1) / 2);
		printf("┃\n");

		x += h;
		m = 1;
		sign = 1;
		TaylorValue = 0;
		factorial = 1;
	}

	printf("┗");
	for (int i = 0; i < width1; i++)
		printf("━");
	printf("┷");
	for (int i = 0; i < width2; i++)
		printf("━");
	printf("┷");
	for (int i = 0; i < width3; i++)
		printf("━");
	printf("┷");
	for (int i = 0; i < width4; i++)
		printf("━");
	printf("┛\n");

	return 0;
}
