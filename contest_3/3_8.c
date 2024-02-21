#include <stdio.h>


#define max(a, b) (((a) > (b)) ? (a) : (b))


int medium(int a, int b, int c) {
    if (a > b && a > c) {
        return max(b, c);
    }

    if (b > a && b > c) {
        return max(a, c);
    }

    return max(a, b);
}


int main(void) {
    int n;
    scanf("%d", &n);

    int numbers[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", numbers + i);
    }

    for (; n != 1; n -= 2) {
        for (int i = 0; i < n - 2; ++i) {
            numbers[i] = medium(numbers[i], numbers[i + 1], numbers[i + 2]);
        }
    }

    printf("%d", numbers[0]);

    return 0;
}
