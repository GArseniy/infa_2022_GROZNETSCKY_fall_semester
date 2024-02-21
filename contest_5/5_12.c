#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Matrix {
    int **a;
    int *b;
    int n;
} matrix;


matrix matrix_init(int n) {
    matrix m = {
            .a = malloc(n * sizeof(int *)),
            .b = malloc(n * sizeof(int)),
            .n = n
    };

    for (int i = 0; i < n; ++i) {
        m.a[i] = malloc(n * sizeof(int));
    }

    return m;
}


void matrix_read(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        for (int j = 0; j < m.n; ++j) {
            scanf("%d", &m.a[i][j]);
        }
        scanf("%d", &m.b[i]);
    }
}


void matrix_delete(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        free(m.a[i]);
    }

    free(m.a);
    free(m.b);
}


void matrix_permute_lines(matrix m, int i, int j) {
    int *p_tmp = m.a[i];
    m.a[i] = m.a[j];
    m.a[j] = p_tmp;

    int tmp = m.b[i];
    m.b[i] = m.b[j];
    m.b[j] = tmp;
}


void matrix_divide_line(matrix m, int i, int alpha) {
    m.b[i] /= alpha;

    for (int k = 0; k < m.n; ++k) {
        m.a[i][k] /= alpha;
    }
}


void matrix_add_line(matrix m, int i, const int j, int alpha) {
    m.b[i] += alpha * m.b[j];

    for (int k = 0; k < m.n; ++k) {
        m.a[i][k] += alpha * m.a[j][k];
    }
}


void matrix_solve(matrix m) {
    ///< Gaussian integer elimination
    for (int j = 0; j < m.n; ++j) {
        for (int i = j; i < m.n; ++i) {
            if (m.a[i][j] < 0) {
                matrix_divide_line(m, i, -1);
            }
        }

        int is_solved = 0;

        while (!is_solved) {
            int min = INT_MAX, index_min = j;

            for (int i = j; i < m.n; ++i) {
                if (0 < m.a[i][j] && m.a[i][j] < min) {
                    min = m.a[i][j];
                    index_min = i;
                }
            }

            if (index_min != j) {
                matrix_permute_lines(m, index_min, j);
            }

            is_solved = 1;

            for (int i = j + 1; i < m.n; ++i) {
                if (m.a[i][j]) {
                    is_solved = 0;
                    matrix_add_line(m, i, j, -m.a[i][j] / m.a[j][j]);
                }
            }
        }
    }

    ///> Reversed Gaussian integer elimination

    for (int j = m.n - 1; j >= 0; --j) {
        matrix_divide_line(m, j, m.a[j][j]);

        for (int i = j - 1; i >= 0; --i) {
            matrix_add_line(m, i, j, -m.a[i][j]);
        }
    }
}


void matrix_print_b(matrix m) {
    for (int i = 0; i < m.n; ++i) {
        printf("%d\n", m.b[i]);
    }
}


int main(void) {
    int n;
    scanf("%d", &n);

    matrix m = matrix_init(n);
    matrix_read(m);
    matrix_solve(m);
    matrix_print_b(m);
    matrix_delete(m);

    return 0;
}
