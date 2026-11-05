#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    
    if (n > 797161) {
        printf("-1\n");
        return 0;
    }
    
    int count = 0;
    while (n > 0) {
        int remainder = n % 3;
        if (remainder == 1) {
            count++;
            n -= 1;
        } else if (remainder == 2) {
            count++;
            n += 1;
        }
        n /= 3;
    }
    
    printf("%d\n", count);
    
    return 0;
}
