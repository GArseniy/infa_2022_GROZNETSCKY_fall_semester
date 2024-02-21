#include <stdio.h>


int GCD(int a, int b) {
    if (!b) {
        return a;
    }

    return GCD(b, a % b);
}


int main(void) {
    int n;
    scanf("%d", &n);

    int num, den;
    scanf("%d %d", &num, &den);

    for (int i = 1; i < n; ++i) {
        int new_num, new_den;
        scanf("%d %d", &new_num, &new_den);

        num = num * new_den + new_num * den;
        den *= new_den;

        int divider = GCD(num, den);
        num /= divider;
        den /= divider;
    }

    printf("%d %d %d", num / den, num % den, den);

    return 0;
}
