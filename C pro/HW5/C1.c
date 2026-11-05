#include <stdio.h>
#include <string.h>

int main(void) {
    char a[10005] = {0}, b[10005] = {0};

    if (fgets(a, sizeof(a), stdin) != NULL) {
        size_t len = strlen(a);
        if (len > 0 && a[len - 1] == '\n') a[len - 1] = '\0';
    }

    if (fgets(b, sizeof(b), stdin) != NULL) {
        size_t len = strlen(b);
        if (len > 0 && b[len - 1] == '\n') b[len - 1] = '\0';
    }

    int la = (int)strlen(a);
    int lb = (int)strlen(b);
    int max_len = la < lb ? la : lb;

    int ans1 = 0;
    for (int k = max_len; k >= 1; --k) {
        if (strncmp(a, b + lb - k, k) == 0) {
            ans1 = k;
            break;
        }
    }

    int ans2 = 0;
    for (int k = max_len; k >= 1; --k) {
        if (strncmp(a + la - k, b, k) == 0) {
            ans2 = k;
            break;
        }
    }

    printf("%d %d\n", ans1, ans2);
    return 0;
}
