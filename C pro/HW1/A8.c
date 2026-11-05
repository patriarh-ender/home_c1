#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    
    unsigned int result = 0; 
    
    for (int i = 0; i < n; i++) {
        unsigned int x;
        scanf("%u", &x);
        result ^= x;
    }
    
    printf("%u\n", result);
    
    return 0;
}
