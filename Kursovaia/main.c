#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"

void print_help() {
    printf("Temperature Statistics Application\n");
    printf("Usage: app [options]\n");
    printf("Options:\n");
    printf("  -h            Show this help message\n");
    printf("  -f <file.csv> Input CSV file for processing\n");
    printf("  -m <month>    Show statistics only for specific month (1-12)\n");
}

int main(int argc, char *argv[]) {
    char *filename = NULL;
    int target_month = -1;

    if (argc == 1) {
        print_help();
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            target_month = atoi(argv[++i]);
        }
    }

    if (!filename) {
        printf("Error: Input file not specified. Use -f <filename> or -h for help.\n");
        return 1;
    }

    temp_db_t db;
    init_db(&db);
    int errors[13] = {0}; // Массив для подсчета ошибок по месяцам
    
    printf("Loading data from %s...\n\n", filename);
    
    if (!load_csv(&db, filename, errors)) {
        printf("Error: Cannot open file '%s'\n", filename);
        free_db(&db);
        return 1;
    }

    if (db.count > 0) {
        uint16_t year = db.records[0].year; // Берем год из первой записи
        
        // Печатаем шапку таблицы
        printf("-----------------------------------------------------------------\n");
        printf("%-5s | %-7s | %-7s | %-8s | %-5s | %-5s\n", 
               "Month", "NuValue", "ErValue", "MonthAvg", "Min", "Max");
        printf("-----------------------------------------------------------------\n");

        for (int m = 1; m <= 12; m++) {
            // Если задан флаг -m, выводим только нужный месяц
            if (target_month != -1 && target_month != m) {
                continue;
            }

            int nu = month_count(&db, year, m);
            int err = errors[m];
            
            // Если данных нет вообще (и нет ошибок), можно пропустить месяц
            if (nu == 0 && err == 0) continue;

            float avg = month_avg_temp(&db, year, m);
            int min = month_min_temp(&db, year, m);
            int max = month_max_temp(&db, year, m);

            // Вывод строки таблицы (форматирование с выравниванием)
            printf("%-5d | %-7d | %-7d | %-8.2f | %-5d | %-5d\n", 
                   m, nu, err, avg, min, max);
        }
        printf("-----------------------------------------------------------------\n");

        // Если флаг -m не задан, выводим статистику за год
        if (target_month == -1) {
            printf("\n=== Yearly statistics for %d ===\n", year);
            printf("Average: %.2f\n", year_avg_temp(&db, year));
            printf("Min: %d\n", year_min_temp(&db, year));
            printf("Max: %d\n", year_max_temp(&db, year));
        }
    } else {
        printf("Database is empty or all lines are invalid.\n");
    }

    free_db(&db);
    return 0;
}
