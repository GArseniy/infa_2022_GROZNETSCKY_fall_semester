#include <stdio.h>


const int COUNT = 4;


int GCD(int a, int b) {
    if (!b) {
        return a;
    }

    return GCD(b, a % b);
}


int main(void) {
    int result;
    scanf("%d", &result);

    for (int i = 1; i < COUNT; ++i) {
        int x;
        scanf("%d", &x);

        result = GCD(result, x);
    }

    printf("%d", result);

    return 0;
}
