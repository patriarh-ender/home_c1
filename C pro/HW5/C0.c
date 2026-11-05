#include <stdio.h>

int is_subsequence(const char *s, int num) {
    char digits[4];
    digits[0] = '0' + num / 100;
    digits[1] = '0' + (num / 10) % 10;
    digits[2] = '0' + num % 10;
    digits[3] = '\0';

    int pos = 0;
    for (int i = 0; s[i] != '\0' && pos < 3; i++) {
        if (s[i] == digits[pos]) {
            pos++;
        }
    }
    return pos == 3;
}

int main(void) {
    char s[1000005];
    if (scanf("%1000000s", s) != 1) return 1;

    int count = 0;
    for (int num = 100; num <= 999; num++) {
        if (is_subsequence(s, num)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
