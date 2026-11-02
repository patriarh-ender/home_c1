#ifndef TEMP_API_H
#define TEMP_API_H

#include <stdint.h>
#include <stddef.h>

// Структура записи
typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    int8_t   temperature;
} temp_record_t;

// Структура для динамического массива
typedef struct {
    temp_record_t *records;
    size_t count;
    size_t capacity;
} temp_db_t;

// Работа с базой данных (массивом)
void init_db(temp_db_t *db);
void free_db(temp_db_t *db);
void add_record(temp_db_t *db, temp_record_t record);
void delete_record(temp_db_t *db, size_t index);
void sort_db(temp_db_t *db);
void print_db(const temp_db_t *db);
int load_csv(temp_db_t *db, const char *filename);

// Статистика по месяцам
float month_avg_temp(const temp_db_t *db, uint16_t year, uint8_t month);
int   month_min_temp(const temp_db_t *db, uint16_t year, uint8_t month);
int   month_max_temp(const temp_db_t *db, uint16_t year, uint8_t month);

// Статистика за год
float year_avg_temp(const temp_db_t *db, uint16_t year);
int   year_min_temp(const temp_db_t *db, uint16_t year);
int   year_max_temp(const temp_db_t *db, uint16_t year);

#endif
