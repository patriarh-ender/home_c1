#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t n;
    if (scanf("%u", &n) != 1) return 1;
    
    uint32_t result = n ^ 0xFF000000U;
    
    printf("%u\n", result);
    
    return 0;
}
