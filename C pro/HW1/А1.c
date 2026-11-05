#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 1;
    
    int max_val;
    scanf("%d", &max_val);
    
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        int x;
        scanf("%d", &x);
        
        if (x > max_val) {
            max_val = x;
            count = 1;
        } else if (x == max_val) {
            count++;
        }
    }
    
    printf("%d\n", count);
    
    return 0;
}
