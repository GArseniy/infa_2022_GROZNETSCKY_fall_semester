#include <stdio.h>
#include <stdlib.h>


typedef struct Complex {
    long re;
    long im;
} complex;


typedef struct Matrix {
    int n;
    complex **m;
} matrix;


matrix matrix_init(int n) {
    matrix m = {
            .n = n,
            .m = malloc(n * sizeof(complex *))
    };

    for (int i = 0; i < n; ++i) {
        m.m[i] = malloc(n * sizeof(complex));
    }

    return m;
}


void matrix_delete(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        free(m.m[i]);
    }

    free(m.m);
}


void matrix_read(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {
            scanf("%ld %ld", &m.m[i][j].re, &m.m[i][j].im);
        }
    }
}


void matrix_conjugate(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {
            m.m[i][j].im *= -1;
        }
    }
}


void matrix_transpose(matrix m) {
    for (int i = 0; i < m.n - 1; ++i) {
        for (int j = i + 1; j < m.n; ++j) {
            complex tmp = m.m[i][j];
            m.m[i][j] = m.m[j][i];
            m.m[j][i] = tmp;
        }
    }
}


void matrix_write(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {
            printf("%ld %ld ", m.m[i][j].re, m.m[i][j].im);
        }

        printf("\n");
    }
}


int main(void) {
    int n;
    scanf("%d", &n);

    matrix m = matrix_init(n);
    matrix_read(m);
    matrix_conjugate(m);
    matrix_transpose(m);
    matrix_write(m);
    matrix_delete(m);

    return 0;
}
