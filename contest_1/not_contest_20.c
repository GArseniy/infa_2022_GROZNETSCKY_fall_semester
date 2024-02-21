///< FIXME: do not read this code


#include <stdio.h>
#include <math.h>

double normal_f(double x, double c, double d) { ///< normalization
    return x / sqrt(c * c + d * d);
}

int main(void) {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    double asin_n_a, asin_n_b, acos_n_c, acos_n_d;
    asin_n_a = asin(normal_f(a, c, d));
    asin_n_b = asin(normal_f(b, c, d));
    acos_n_c = acos(normal_f(c, c, d));
    acos_n_d = acos(normal_f(d, c, d));
    int is_normal_a = (normal_f(a, c, d) >= 1);
    int is_normal_b = (normal_f(b, c, d) >= 1);
    int is_good_rectangles;
    if (is_normal_a && is_normal_b) {
        is_good_rectangles = 1;
    } else if (is_normal_a) {
        is_good_rectangles = fmax(0, -M_PI - asin_n_b - acos_n_c) - (asin_n_b - acos_n_c) <= 0.0005;
    } else if (is_normal_b) {
        is_good_rectangles = fmax(0, -M_PI - asin_n_a - acos_n_d) - (asin_n_a - acos_n_d) <= 0.0005;
    } else {
        double left_border_of_alpha, right_border_of_alpha;
        left_border_of_alpha = -M_PI - fmin(asin_n_a + acos_n_d, asin_n_b + acos_n_c);
        right_border_of_alpha = fmin(asin_n_a - acos_n_d, asin_n_b - acos_n_c);
        left_border_of_alpha = fmax(left_border_of_alpha, 0);
        is_good_rectangles = left_border_of_alpha - right_border_of_alpha <= 0.0005;
    }
    if (is_good_rectangles) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}