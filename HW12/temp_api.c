#include "temp_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Управление динамическим массивом ---

void init_db(temp_db_t *db) {
    db->records = NULL;
    db->count = 0;
    db->capacity = 0;
}

void free_db(temp_db_t *db) {
    free(db->records);
    db->records = NULL;
    db->count = 0;
    db->capacity = 0;
}

void add_record(temp_db_t *db, temp_record_t record) {
    if (db->count >= db->capacity) {
        db->capacity = db->capacity == 0 ? 10 : db->capacity * 2;
        db->records = realloc(db->records, db->capacity * sizeof(temp_record_t));
    }
    db->records[db->count++] = record;
}

void delete_record(temp_db_t *db, size_t index) {
    if (index >= db->count) return;
    // Сдвигаем элементы влево
    for (size_t i = index; i < db->count - 1; i++) {
        db->records[i] = db->records[i + 1];
    }
    db->count--;
}

// Компаратор для qsort (сортировка по дате и времени)
static int compare_records(const void *a, const void *b) {
    const temp_record_t *ra = (const temp_record_t *)a;
    const temp_record_t *rb = (const temp_record_t *)b;
    if (ra->year != rb->year) return ra->year - rb->year;
    if (ra->month != rb->month) return ra->month - rb->month;
    if (ra->day != rb->day) return ra->day - rb->day;
    if (ra->hour != rb->hour) return ra->hour - rb->hour;
    return ra->minute - rb->minute;
}

void sort_db(temp_db_t *db) {
    if (db->count > 0) {
        qsort(db->records, db->count, sizeof(temp_record_t), compare_records);
    }
}

void print_db(const temp_db_t *db) {
    printf("--- Database (%zu records) ---\n", db->count);
    for (size_t i = 0; i < db->count; i++) {
        printf("%04d-%02d-%02d %02d:%02d | %d\n",
               db->records[i].year, db->records[i].month, db->records[i].day,
               db->records[i].hour, db->records[i].minute, db->records[i].temperature);
    }
}

// Загрузка из CSV. Ожидаемый формат: 2024;1;15;12;30;-5
int load_csv(temp_db_t *db, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        temp_record_t r;
        // Пытаемся прочитать через ';' или ','
        if (sscanf(line, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.temperature) == 6 ||
            sscanf(line, "%hu,%hhu,%hhu,%hhu,%hhu,%hhd", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.temperature) == 6) {
            add_record(db, r);
        }
    }
    fclose(f);
    return 1;
}

// --- Статистика ---

float month_avg_temp(const temp_db_t *db, uint16_t year, uint8_t month) {
    long sum = 0; size_t cnt = 0;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].month == month) {
            sum += db->records[i].temperature;
            cnt++;
        }
    }
    return cnt ? (float)sum / cnt : 0.0f;
}

int month_min_temp(const temp_db_t *db, uint16_t year, uint8_t month) {
    int min = 100;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].month == month && db->records[i].temperature < min) {
            min = db->records[i].temperature;
        }
    }
    return (min == 100) ? 0 : min;
}

int month_max_temp(const temp_db_t *db, uint16_t year, uint8_t month) {
    int max = -100;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].month == month && db->records[i].temperature > max) {
            max = db->records[i].temperature;
        }
    }
    return (max == -100) ? 0 : max;
}

float year_avg_temp(const temp_db_t *db, uint16_t year) {
    long sum = 0; size_t cnt = 0;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year) {
            sum += db->records[i].temperature;
            cnt++;
        }
    }
    return cnt ? (float)sum / cnt : 0.0f;
}

int year_min_temp(const temp_db_t *db, uint16_t year) {
    int min = 100;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].temperature < min) min = db->records[i].temperature;
    }
    return (min == 100) ? 0 : min;
}

int year_max_temp(const temp_db_t *db, uint16_t year) {
    int max = -100;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].temperature > max) max = db->records[i].temperature;
    }
    return (max == -100) ? 0 : max;
}
