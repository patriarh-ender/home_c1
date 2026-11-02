#include "temp_api.h"

// Вспомогательная функция: проверяет, подходит ли запись под нужный год и месяц
static int is_month(const temp_record_t *r, uint16_t y, uint8_t m) {
    return (r->year == y && r->month == m);
}

// Вспомогательная функция: проверяет, подходит ли запись под нужный год
static int is_year(const temp_record_t *r, uint16_t y) {
    return r->year == y;
}

// --- СТАТИСТИКА ПО МЕСЯЦУ ---
float month_avg_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month) {
    long sum = 0; size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        if (is_month(&data[i], year, month)) {
            sum += data[i].temperature;
            count++;
        }
    }
    return count ? (float)sum / count : 0.0f;
}

int month_min_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month) {
    int min = 100; // заведомо больше максимально возможной
    for (size_t i = 0; i < n; i++) {
        if (is_month(&data[i], year, month) && data[i].temperature < min) {
            min = data[i].temperature;
        }
    }
    return (min == 100) ? 0 : min;
}

int month_max_temp(const temp_record_t *data, size_t n, uint16_t year, uint8_t month) {
    int max = -100; // заведомо меньше минимально возможной
    for (size_t i = 0; i < n; i++) {
        if (is_month(&data[i], year, month) && data[i].temperature > max) {
            max = data[i].temperature;
        }
    }
    return (max == -100) ? 0 : max;
}

// --- СТАТИСТИКА ЗА ГОД ---
float year_avg_temp(const temp_record_t *data, size_t n, uint16_t year) {
    long sum = 0; size_t count = 0;
    for (size_t i = 0; i < n; i++) {
        if (is_year(&data[i], year)) {
            sum += data[i].temperature;
            count++;
        }
    }
    return count ? (float)sum / count : 0.0f;
}

int year_min_temp(const temp_record_t *data, size_t n, uint16_t year) {
    int min = 100;
    for (size_t i = 0; i < n; i++) {
        if (is_year(&data[i], year) && data[i].temperature < min) {
            min = data[i].temperature;
        }
    }
    return (min == 100) ? 0 : min;
}

int year_max_temp(const temp_record_t *data, size_t n, uint16_t year) {
    int max = -100;
    for (size_t i = 0; i < n; i++) {
        if (is_year(&data[i], year) && data[i].temperature > max) {
            max = data[i].temperature;
        }
    }
    return (max == -100) ? 0 : max;
}
