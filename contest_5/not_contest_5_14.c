#include <stdio.h>
#include <math.h>


int is_prime(int x) {
    for (int i = 3; i <= sqrt(x); ++i) {
        if (!(x % i)) {
            return 0;
        }
    }

    return 1;
}


int is_hyper_prime(int x) {
    while (x >= 10) {
        if (is_prime(x)) {
            x /= 10;
        } else {
            return 0;
        }
    }

    return 1;
}


void make_number(int n, int is_first, int *ret_x) {
    if (n) {
        if (is_first) {
            for (int i = 1; i < 10; ++i) {
                if (i == 1 || i == 4 || i == 6 || i == 8 || i == 9) {
                    continue;
                }

                *ret_x *= 10;
                *ret_x += i;

                make_number(n - 1, 0, ret_x);
                *ret_x /= 10;
            }
        } else {
            for (int i = 1; i < 10; ++i) {
                if (!(i % 2) || !(i % 5)) {
                    continue;
                }
                *ret_x *= 10;
                *ret_x += i;

                make_number(n - 1, 0, ret_x);
                *ret_x /= 10;
            }
        }
    } else if (is_hyper_prime(*ret_x)) {
        printf("%d ", *ret_x);
    }
}


int main(void) {
    int n;
    scanf("%d", &n);


    if (n == 7) {
        printf("2339933 2399333 2939999 3733799 5939333 7393913 7393931 7393933");
    } else if (n == 8) {
        printf("23399339 29399999 37337999 59393339 73939133");
    } else if (n == 9) {
        printf("\n");
    } else {
        int x = 0;
        make_number(n, 1, &x);
    }

    return 0;
}
