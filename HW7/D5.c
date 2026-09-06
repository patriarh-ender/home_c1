
#include <stdio.h>

void rec(int a) {
    if (a >= 2)        
         rec(a / 2);
    printf("%d", a % 2);
               
}

int main() {
    int a;
    scanf("%d", &a);
    if (a == 0) {
        printf("0");   
    } 
    //~ else if (a==1){
        //~ printf("0001");   
    //~ } 
    else {
        rec(a);
    }
    return 0;
}

