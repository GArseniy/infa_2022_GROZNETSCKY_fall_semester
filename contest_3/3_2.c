#include <stdio.h>


int is_prime(int x) {
    if (x < 2) {
        return 0;
    }

    for (int i = 2; i * i <= x; ++i) {
        if (!(x % i)) {
            return 0;
        }
    }

    return 1;
}


int main(void) {
    int n;
    scanf("%d", &n);

    while (!is_prime(n++));

    printf("%d", --n);

    return 0;
}
