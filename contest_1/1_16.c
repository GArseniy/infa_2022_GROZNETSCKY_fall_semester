#include <stdio.h>


int main(void) {
    double x1, x2, x3, y1, y2, y3;

    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);
    scanf("%lf %lf", &x3, &y3);

    printf("%.4lf %.4lf", (x1 + x2 + x3) / 3, (y1 + y2 + y3) / 3);

    return 0;
}
