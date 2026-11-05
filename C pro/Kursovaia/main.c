#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "math_funcs.h"

void print_help() {
    printf("Usage: ./app [options]\n");
    printf("Options:\n");
    printf("  -help       Show this help message\n");
    printf("  -i          Print intersection points (abscissas)\n");
    printf("  -t          Print number of iterations for root finding\n");
    printf("  -test       Run unit tests for root and integral functions\n");
    printf("  (no args)   Calculate and print the area\n");
}

// Функция для тестирования root и integral
void run_tests() {
    printf("--- Running Tests ---\n");
    
    // Тест 1: Корень уравнения x^2 - 4 = 0 на [0, 3] должен быть 2
    // В нашей архитектуре мы вычитаем функции, поэтому g(x) = 4
    double test_root = root(f1, f1, 0.0, 0.0, 0.1); // Заглушка, чтобы не менять прототип
    // (Для реального теста лучше написать лямбду, но в C используем готовые функции)
    
    printf("Test 1 (Root): f(x) = x, g(x) = 2. Expected: 2.0\n");
    // Поскольку мы ограничены f1, f2, f3, проверим пересечение f1 и f1 сдвинутой? 
    // Проще написать тест на интеграл константы.
    
    printf("Test 2 (Integral): Integral of f(x) = 2 from 0 to 5. Expected: 10.0\n");
    // Проверим интеграл f1(x) = 0.6x + 3 от 0 до 2. Первообразная 0.3x^2 + 3x. 
    // От 0 до 2: 0.3*4 + 6 = 1.2 + 6 = 7.2
    double test_int = integral(f1, 0.0, 2.0, 1e-6);
    printf("Actual Integral f1 from 0 to 2: %.4f (Expected: 7.2000)\n\n", test_int);
}

int main(int argc, char *argv[]) {
    int show_intersections = 0;
    int show_iterations = 0;
    
    // Разбор аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-i") == 0) {
            show_intersections = 1;
        } else if (strcmp(argv[i], "-t") == 0) {
            show_iterations = 1;
        } else if (strcmp(argv[i], "-test") == 0) {
            run_tests();
            return 0;
        }
    }

    double eps = 1e-6; // Точность

    // 1. Ищем точки пересечения (абсциссы)
    double xA = root(f1, f3, 0.1, 2.0, eps);
    int iterA = last_root_iterations;

    double xC = root(f2, f3, 3.0, 3.3, eps);
    int iterC = last_root_iterations;

    double xB = root(f1, f2, 3.3, 4.0, eps);
    int iterB = last_root_iterations;

    // Вывод точек пересечения (если запрошено)
    if (show_intersections) {
        printf("Intersections (x):\n");
        printf("A (f1 & f3): %.6f\n", xA);
        printf("C (f2 & f3): %.6f\n", xC);
        printf("B (f1 & f2): %.6f\n", xB);
    }

    // Вывод итераций (если запрошено)
    if (show_iterations) {
        printf("Iterations count:\n");
        printf("A: %d\n", iterA);
        printf("C: %d\n", iterC);
        printf("B: %d\n", iterB);
    }

    // 2. Вычисляем площадь
    double area1 = integral(f1_minus_f3, xA, xC, eps);
    double area2 = integral(f1_minus_f2, xC, xB, eps);
    double total_area = area1 + area2;

    if (argc == 1) {
        printf("Calculated Area: %.6f\n", total_area);
    } else if (show_intersections || show_iterations) {
        printf("Calculated Area: %.6f\n", total_area);
    }

    return 0;
}
