#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void) {
    int x, y;
    scanf("%d %d", &x, &y);

    x = abs(x);
    y = abs(y);

    int cnt = fmin(x, y) * 2;

    int abs_diff = abs(x - y);
    cnt += abs_diff * 2 - abs_diff % 2;

    printf("%d", cnt);

    return 0;
}
