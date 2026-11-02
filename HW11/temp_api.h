#ifndef TEMP_API_H
#define TEMP_API_H

#include <stdint.h> // используем точные типы (int8_t, uint16_t и т.д.)
#include <stddef.h> // для size_t

// Наша структура по заданию
typedef struct {
    uint16_t year;       // год 4 цифры (dddd)
    uint8_t  month;      // месяц 2 цифры (mm)
    uint8_t  day;        // день 2 цифры (dd)
    uint8_t  hour;       // часы 2 цифры (hh)
    uint8_t  minute;     // минуты 2 цифры (mm)
    int8_t   temperature;// температура от -99 до 99
} temp_record_t;

// Прототипы функций по месяцам
float month_avg_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month);
int   month_min_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month);
int   month_max_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month);

// Прототипы функций за год
float year_avg_temp(const temp_record_t *data, size_t n, uint16_t year);
int   year_min_temp(const temp_record_t *data, size_t n, uint16_t year);
int   year_max_temp(const temp_record_t *data, size_t n, uint16_t year);

#endif
