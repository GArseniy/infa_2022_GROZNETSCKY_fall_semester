#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int used[n + 1];

    for (int i = 0; i < n + 1; ++i) {
        used[i] = 0;
    }

    int result = 1;

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);

        if (x <= 0 || x > n || used[x]) {
            result = 0;
            break;
        }

        used[x] = 1;
    }

    if (result) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}
