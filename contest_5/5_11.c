#include <stdio.h>


int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);

    int matrix[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int j = 1; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            int max_prev = matrix[i][j - 1];

            if (i - 1 >= 0 && matrix[i - 1][j - 1] > max_prev) {
                max_prev = matrix[i - 1][j - 1];
            }
            if (i + 1 < n && matrix[i + 1][j - 1] > max_prev) {
                max_prev = matrix[i + 1][j - 1];
            }

            matrix[i][j] += max_prev;
        }
    }

    int max_n = matrix[n - 1][m - 1];

    for (int i = 0; i < n; ++i) {
        if (matrix[i][m - 1] > max_n) {
            max_n = matrix[i][m - 1];
        }
    }

    printf("%d", max_n);

    return 0;
}
