#include <stdio.h>
#include <stdlib.h>


void matrix_multiply(long **m, long **x, int k, int p) {
    long res[k][k];

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            long sum = 0;

            for (int s = 0; s < k; ++s) {
                sum += m[i][s] * x[s][j];
            }

            res[i][j] = sum % p;
        }
    }

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            m[i][j] = res[i][j];
        }
    }
}


long **matrix_bin_pow(long **a, int k, int n, int p) {
    long **ret = malloc(k * sizeof(long *));

    for (int i = 0; i < k; ++i) {
        ret[i] = malloc(k * sizeof(long));
    }

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            ret[i][j] = (i == j);
        }
    }

    long pow = 1;

    while (pow <= n) {
        if ((n / pow) % 2) {
            matrix_multiply(ret, a, k, p);
        }

        matrix_multiply(a, a, k, p);

        pow *= 2;
    }

    return ret;
}


long dot_product(long **a_pow, long const *f, int k, int p) {
    long sum = 0;

    for (int i = 1; i <= k; ++i) {
        sum += a_pow[0][i - 1] * f[k - i];
    }

    return (p + sum % p) % p;
}


void matrix_delete(long **a, int k) {
    for (int i = 0; i < k; ++i) {
        free(a[i]);
    }

    free(a);
}


#define READ_F \
    long f[k];\
    for (int i = 0; i < k; ++i) {\
        scanf("%ld", f + i);\
    }


#define READ_A \
    long **a = malloc(k * sizeof(long *)); \
    \
    for (int i = 0; i < k; ++i) {\
        a[i] = malloc(k * sizeof(long));\
    }\
    \
    for (int i = 0; i < k; ++i) {\
        scanf("%ld", &a[0][i]);\
    }\
    \
    for (int i = 1; i < k; ++i) {\
        for (int j = 0; j < k; ++j) {\
            a[i][j] = (i == j + 1);\
        }\
    }


int main(void) {
    long k, n, p;
    scanf("%ld %ld %ld", &k, &n, &p);

    READ_F
    READ_A

    if (n <= k) {
        printf("%ld", (p + f[n - 1] % p) % p);
        return 0;
    }

    long **a_pow = matrix_bin_pow(a, k, n - k, p);
    printf("%ld", dot_product(a_pow, f, k, p));

    matrix_delete(a, k);
    matrix_delete(a_pow, k);

    return 0;
}
