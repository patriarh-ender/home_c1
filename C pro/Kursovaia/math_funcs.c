#include "math_funcs.h"
#include <math.h>

/* 
 * ГЛОБАЛЬНАЯ ПЕРЕМЕННАЯ: 
 * Хранит количество итераций, которое потребовалось функции root()
 * для нахождения последнего корня. Используется для вывода статистики.
 */
int last_root_iterations = 0;

// --- Исходные функции ---
double f1(double x) { return 0.6 * x + 3.0; }
double f2(double x) { return pow(x - 2.0, 3) - 1.0; }
double f3(double x) { return 3.0 / x; }

// --- Вспомогательные функции для интегралов ---
double f1_minus_f3(double x) { return f1(x) - f3(x); }
double f1_minus_f2(double x) { return f1(x) - f2(x); }

// --- Поиск корня методом бисекции (деления пополам) ---
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1) {
    double mid;
    last_root_iterations = 0;
    
    while ((b - a) > eps1) {
        mid = (a + b) / 2.0;
        // Если знаки f(a)-g(a) и f(mid)-g(mid) разные, корень в левой половине
        if ((f(mid) - g(mid)) * (f(a) - g(a)) <= 0) {
            b = mid;
        } else {
            a = mid;
        }
        last_root_iterations++;
    }
    return (a + b) / 2.0;
}

// --- Вычисление интеграла методом Симпсона ---
double integral(double (*f)(double), double a, double b, double eps2) {
    int n = 100; // Начальное количество разбиений
    double prev_res = 0, res = 0;
    
    do {
        prev_res = res;
        double h = (b - a) / n;
        double sum = f(a) + f(b);
        
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
        }
        
        res = sum * h / 3.0;
        n *= 2; // Удваиваем разбиение, пока не достигнем точности
        
    } while (fabs(res - prev_res) > eps2 && n < 1000000);
    
    return res;
}
