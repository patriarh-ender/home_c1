#include <stdio.h>
#include "temp_api.h"

int main(void) {
    temp_record_t data[] = {
        {2024, 1, 15, 12, 30, -5},
        {2024, 1, 20,  3,  0, -12},
        {2024, 1, 25, 14, 45,  1},
        {2024, 2,  3,  9, 15, -3},
        {2024, 2, 14, 18, 20,  4},
        {2024, 7, 10, 13, 30, 27},
    };
    
    size_t n = sizeof(data) / sizeof(data[0]);
    uint16_t year = 2024;

    printf("=== Monthly statistics for %d ===\n", year);
    
    for (uint8_t m = 1; m <= 2; m++) {
        printf("Month %d:\n", m);
        printf("  Average: %.2f\n", month_avg_temp(data, n, year, m));
        printf("  Min: %d\n", month_min_temp(data, n, year, m));
        printf("  Max: %d\n", month_max_temp(data, n, year, m));
    }

    printf("\n=== Yearly statistics ===\n");
    printf("Year average: %.2f\n", year_avg_temp(data, n, year));
    printf("Year min: %d\n", year_min_temp(data, n, year));
    printf("Year max: %d\n", year_max_temp(data, n, year));

    return 0;
}