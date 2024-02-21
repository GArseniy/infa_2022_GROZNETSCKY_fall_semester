#include <stdio.h>


int main(void) {
    double x;
    int n;
    scanf("%lf %d", &x, &n);

    double result = 0;

    double dynamic_summand = x;
    int fact = 1;
    x *= x;

    for (int i = 1; i <= n; ++i) {
        result += dynamic_summand;
        dynamic_summand *= -x / (fact + 1) / (fact + 2);
        fact += 2;
    }

    printf("%.6lf", result);

    return 0;
}
