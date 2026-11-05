#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t n;
    int k;
    
    if (scanf("%u %d", &n, &k) != 2) return 1;
    
    uint32_t mask = (1U << k) - 1;
    uint32_t result = n & mask;
    
    printf("%u\n", result);
    
    return 0;
}
