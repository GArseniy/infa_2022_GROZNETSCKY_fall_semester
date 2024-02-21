#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int permutation[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", permutation + i);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", permutation[permutation[permutation[i] - 1] - 1]);
    }

    return 0;
}
