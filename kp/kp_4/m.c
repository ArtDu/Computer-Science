/*  Автор: Дубинин Артем
    Группа М80-103Б
    Практикум по курсам "Основы информатики", "Алгоритмы и структуры данных"
    Задание 4.*/
#include <stdio.h>
#include <string.h>
#include <math.h>
const int width1 = 28;
const int width2 = 9;
const int width3 = 14;
const int width4 = 14;
const int width5 = 14;
double eps = 0.000001;
const double a1 = 2;
const double b1 = 3;
const double a2 = 2;
const double b2 = 3;

double F1(double x) {
	return 0.6*pow(3,x)-2.3*x-3;
}

double F2(double x) {
	return x*x - log(1+x)-3;
}

double xf1(double x) { // x = всё остальное
	return log((2.3*x+3)/(0.6)) / log(3);
}

double xf2(double x) {
	return sqrt(log(1+x)+3);
}

double derF1(double x) { //произодная
	return 0.6*pow(3,x)*log(3)-2.3;
}

double derF2(double x) {
	return 2*x-((1)/(1+x));
}

double dichotomy(double (*f)(double), double a, double b) {
	while (fabs(a - b) >= eps) {
		if (f(a) * f((a + b) / 2) > 0)
			a = (a + b) / 2;
		else if (f(b) * f((a + b) / 2) > 0)
			b = (a + b) / 2;
		else
			return (a + b) / 2;
	}
	return (a + b) / 2;
}

double iterative(double (*f)(double), double a, double b) {
	double nx, x;	
	x = (a + b) / 2;
    nx = f(x);
	while (fabs(nx - x) >= eps) {
		x = nx;
		nx = f(x);
	}
	return nx;
}

double newton(double (*f)(double), double (*derf)(double), double a, double b) {
	double x, nx;
	x = (a + b) / 2;
	nx = x - f(x) / derf(x);
	while (fabs(nx - x) >= eps) {
		x = nx;
		nx = x - f(x) / derf(x);
	}
	return nx;
}

int main() {
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
	printf("┯");
	for (int i = 0; i < width5; i++)
		printf("━");
	printf("┓\n");
	printf("┃");
	printf("%-*s", width1, "Function");
	printf("│");
	printf("%-*s", width2, "Segment");
	printf("│");
	printf("%-*s", width3, "Dichotomy");
	printf("│");
	printf("%-*s", width4, "Iterative");
	printf("│");
	printf("%-*s", width5, "Newton");
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
	printf("┼");
	for (int i = 0; i < width5; i++)
		printf("─");
	printf("┨\n");
	printf("┃%-*s", width1, "0.6 * 3^x - 2.3x - 3 = 0   ");
	printf("│[%.1lf,%.1lf]", a1, b1);
	printf("│%-*.5lf", width3, dichotomy(F1, a1, b1));
	printf("│%-*.5lf", width4, iterative(xf1, a1, b1));
	printf("│ -----        ┃\n", width5 );
	printf("┃%-*s", width1, "x^2 + ln(1+x) - 3 = 0");
	printf("│[%.1lf,%.1lf]", a2, b2);
	printf("│%-*.5lf", width3, dichotomy(F2, a2, b2));
	printf("│%-*.5lf", width4, iterative(xf2, a2, b2));
	printf("│%-*.5lf┃\n", width5, newton(F2, derF2, a2, b2));
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
	printf("┷");
	for (int i = 0; i < width5; i++)
		printf("━");
	printf("┛\n");
	return 0;
}

