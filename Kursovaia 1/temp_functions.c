#include "temp_functions.h"
#include <stdio.h>
#include <stdlib.h>

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

int load_csv(temp_db_t *db, const char *filename, int errors[13]) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[256];
    int line_num = 0;
    for(int i = 0; i <= 12; i++) errors[i] = 0;
    
    while (fgets(line, sizeof(line), f)) {
        line_num++;
        temp_record_t r;
        // Проверяем, что считались ровно 6 чисел
        if (sscanf(line, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", &r.year, &r.month, &r.day, &r.hour, &r.minute, &r.temperature) == 6) {
            add_record(db, r);
        } else {
            // Ошибка формата: выводим строку и пытаемся запомнить месяц для статистики
            printf("Error in line %d: Invalid CSV format. Skipping.\n", line_num);
            unsigned short y; unsigned char m;
            if (sscanf(line, "%hu;%hhu", &y, &m) == 2 && m >= 1 && m <= 12) {
                errors[m]++;
            }
        }
    }
    fclose(f);
    return 1;
}

int month_count(const temp_db_t *db, uint16_t year, uint8_t month) {
    int cnt = 0;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].month == month) cnt++;
    }
    return cnt;
}

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
        if (db->records[i].year == year && db->records[i].temperature < min) {
            min = db->records[i].temperature;
        }
    }
    return (min == 100) ? 0 : min;
}

int year_max_temp(const temp_db_t *db, uint16_t year) {
    int max = -100;
    for (size_t i = 0; i < db->count; i++) {
        if (db->records[i].year == year && db->records[i].temperature > max) {
            max = db->records[i].temperature;
        }
    }
    return (max == -100) ? 0 : max;
}
