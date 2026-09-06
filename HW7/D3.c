
#include <stdio.h>

void rec(int a) {
    if (a == 0)        
        return;
    printf("%2d", a % 10);
    rec(a / 10);           
}

int main() {
    int a;
    scanf("%d", &a);
    if (a == 0) {
        printf("0");   
    } else {
        rec(a);
    }
    return 0;
}
