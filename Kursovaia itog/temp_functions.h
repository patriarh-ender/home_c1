#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>

// Структура для хранения одной записи
typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    int8_t   temperature;
} temp_record_t;

// Структура для динамического массива (как и рекомендовано в ТЗ)
typedef struct {
    temp_record_t *records;
    size_t count;
    size_t capacity;
} temp_db_t;

// Инициализация и очистка памяти
void init_db(temp_db_t *db);
void free_db(temp_db_t *db);

// Добавление и загрузка из файла
void add_record(temp_db_t *db, temp_record_t record);
int load_csv(temp_db_t *db, const char *filename);

// Функции статистики по месяцам
float month_avg_temp(const temp_db_t *db, uint16_t year, uint8_t month);
int   month_min_temp(const temp_db_t *db, uint16_t year, uint8_t month);
int   month_max_temp(const temp_db_t *db, uint16_t year, uint8_t month);

// Функции статистики за год
float year_avg_temp(const temp_db_t *db, uint16_t year);
int   year_min_temp(const temp_db_t *db, uint16_t year);
int   year_max_temp(const temp_db_t *db, uint16_t year);

#endif // TEMP_FUNCTIONS_H
