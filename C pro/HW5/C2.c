#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 10000

int stack[MAX_SIZE];
int top = -1;

int main(void) {
    int c;
    int num = 0;
    int in_num = 0; 

    while ((c = getchar()) != EOF && c != '.') {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            in_num = 1;
        } 
        else if (c == ' ') {
            if (in_num) {
                stack[++top] = num;
                num = 0;
                in_num = 0;
            }
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == 'x' || c == 'X') {
            if (in_num) { 
                stack[++top] = num;
                num = 0;
                in_num = 0;
            }
            int a = stack[top--];
            int b = stack[top--];
            
            if (c == '+') stack[++top] = b + a;
            else if (c == '-') stack[++top] = b - a;
            else if (c == '*' || c == 'x' || c == 'X') stack[++top] = b * a;
            else if (c == '/') stack[++top] = b / a;
        }
    }

    if (in_num) {
        stack[++top] = num;
    }

    printf("%d\n", stack[top]);

    return 0;
}
