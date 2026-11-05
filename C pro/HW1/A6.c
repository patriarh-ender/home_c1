#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t n;
    if (scanf("%u", &n) != 1) return 1;
    
    int count = 0;
    while (n > 0) {
        n = n & (n - 1);
        count++;
    }
    
    printf("%d\n", count);
    
    return 0;
}
