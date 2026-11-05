#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    
    n = n % 26;
    
    int c;
    while ((c = getchar()) != '.') {
        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + n) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + n) % 26;
        }
        putchar(c);
    }
    
    putchar('.');
    putchar('\n');
    
    return 0;
}
