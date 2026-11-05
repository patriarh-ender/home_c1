#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t n;
    int k;
    
    if (scanf("%u %d", &n, &k) != 2) return 1;
    
    uint32_t mask = (1U << k) - 1;
    uint32_t max_val = 0;
    
    for (int i = 0; i <= 32 - k; i++) {
        uint32_t current_val = (n >> i) & mask;
        if (current_val > max_val) {
            max_val = current_val;
        }
    }
    
    printf("%u\n", max_val);
    
    return 0;
}
