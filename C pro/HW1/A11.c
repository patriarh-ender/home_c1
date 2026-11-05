#include <stdio.h>

int extractExp(float x) {
    union {
        float f;
        unsigned int u;
    } converter;
    
    converter.f = x;
    return (converter.u >> 23) & 0xFF;
}

int main(void) {
    float x;
    if (scanf("%f", &x) == 1) {
        printf("%d\n", extractExp(x));
    }
    return 0;
}
