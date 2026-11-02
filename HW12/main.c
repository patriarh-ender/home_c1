#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_api.h"

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
    int target_month = -1; // -1 значит выводим всё

    // 1. Разбор аргументов командной строки
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

    // 2. Инициализация и загрузка данных
    temp_db_t db;
    init_db(&db);
    
    if (!load_csv(&db, filename)) {
        printf("Error: Cannot open file '%s'\n", filename);
        return 1;
    }

    // 3. Сортировка (демонстрация функции)
    sort_db(&db);
    
    // 4. Вывод статистики
    if (db.count > 0) {
        uint16_t year = db.records[0].year; // Берем год из первой записи
        
        if (target_month >= 1 && target_month <= 12) {
            // Вывод только за указанный месяц
            printf("=== Statistics for %d, month %d ===\n", year, target_month);
            printf("Average: %.2f\n", month_avg_temp(&db, year, (uint8_t)target_month));
            printf("Min: %d\n", month_min_temp(&db, year, (uint8_t)target_month));
            printf("Max: %d\n", month_max_temp(&db, year, (uint8_t)target_month));
        } else {
            // Вывод по всем месяцам (упрощенно - выводим за 1, 2 и весь год)
            printf("=== Monthly statistics for %d ===\n", year);
            for (int m = 1; m <= 12; m++) {
                // Печатаем только если данные за этот месяц есть
                if (month_avg_temp(&db, year, m) != 0.0f || month_min_temp(&db, year, m) != 0) {
                     printf("Month %2d: Avg=%.2f, Min=%d, Max=%d\n",
                            m, month_avg_temp(&db, year, m), month_min_temp(&db, year, m), month_max_temp(&db, year, m));
                }
            }
            printf("\n=== Yearly statistics ===\n");
            printf("Average: %.2f\n", year_avg_temp(&db, year));
            printf("Min: %d\n", year_min_temp(&db, year));
            printf("Max: %d\n", year_max_temp(&db, year));
        }
    } else {
        printf("Database is empty.\n");
    }

    free_db(&db);
    return 0;
}
