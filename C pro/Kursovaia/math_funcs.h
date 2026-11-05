#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

// Прототипы исходных функций
double f1(double x);
double f2(double x);
double f3(double x);

// Прототипы функций разности (для поиска корней и интегралов)
double f1_minus_f3(double x);
double f1_minus_f2(double x);

// Функция поиска корня уравнения f(x) = g(x) на отрезке [a, b] с точностью eps1
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1);

// Функция вычисления определенного интеграла от f(x) на [a, b] с точностью eps2
double integral(double (*f)(double), double a, double b, double eps2);

// Глобальная переменная для хранения количества итераций (документировано в .c)
extern int last_root_iterations;

#endif // MATH_FUNCS_H
