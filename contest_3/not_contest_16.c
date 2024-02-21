#include <stdio.h>


int pow_f(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y == 1) {
        return x;
    } else {
        return (x * pow_f(x, y - 1));
    }
}


int main(void) {
    int a, b, c, m, maximum;
    scanf("%d %d %d %d", &a, &b, &c, &m);
    printf("%d %d %d\n", a, b, c);
    a = pow_f(a, b * c);
    b = pow_f(b, a * c);
    c = pow_f(c, b * a);
    printf("%d %d %d\n", a, b, c);
    maximum = a;
    if ((b > a) && (b > c)) {
        maximum = b;
    } else if ((c > a) && (c > b)) {
        maximum = c;
    }
    printf("%d", maximum);
    return 0;
}
