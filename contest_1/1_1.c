#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int x;
    scanf("%d", &x);

    int max = x;
    int min = x;

    for (int i = 1; i < n; ++i) {
        scanf("%d", &x);

        if (x > max) {
            max = x;
        } else if (x < min) {
            min = x;
        }
    }

    printf("%d", max - min);

    return 0;
}
