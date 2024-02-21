#include <stdio.h>


const int MOD = 2010;
const int BASE_SYSTEM = 10;


int concat(int x, int y) {
    int degree = 1;

    while (y / degree > 0) {
        degree *= BASE_SYSTEM;
    }

    return degree * x + y;
}


int main(void) {
    int n, a;
    scanf("%d %d", &n, &a);

    int x = n % MOD;
    int is_in = 0;

    for (int i = 0; i < MOD; ++i) {
        if (a == x) {
            is_in = 1;
            break;
        }

        x = concat(x, x) % MOD;
    }

    printf(is_in ? "YES" : "NO");

    return 0;
}
