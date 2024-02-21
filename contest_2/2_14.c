#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int used[n];

    for (int i = 0; i < n; ++i) {
        used[i] = 0;
    }

    int result = 1;
    int permutation[n];

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);

        if (x + i >= n) {
            result = 0;
            break;
        }

        int j = n - 1;

        while (x > 0) {
            x -= !used[j--];
        }

        while (used[j--]);
        ++j;

        permutation[i] = j + 1;
        used[j] = 1;
    }

    if (result) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", permutation[i]);
        }
    } else {
        printf("-1");
    }

    return 0;
}
