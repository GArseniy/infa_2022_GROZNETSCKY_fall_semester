#include <stdio.h>


#define PRINT { \
    for (int i = 0; i < n; ++i) {\
        for (int j = 0; j < m; ++j) {\
            printf("%d ", matrix[i][j]);\
        }\
        printf("\n");\
    }\
    printf("\n");\
}


int main(void) {
    int n, m, k;
    scanf("%d %d %d", &m, &n, &k);

    int matrix[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < k; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        matrix[x - 1][y - 1] = 1;
    }

    int time = 0, dead = 0;

    while (!dead) {
        //PRINT
        ++time;
        int copy[n][m];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                copy[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j]) {
                    if (i - 1 >= 0) {
                        ++copy[i - 1][j];
                    }
                    if (i + 1 < n) {
                        ++copy[i + 1][j];
                    }
                    if (j - 1 >= 0) {
                        ++copy[i][j - 1];
                    }
                    if (j + 1 < m) {
                        ++copy[i][j + 1];
                    }
                    matrix[i][j] = -100;
                }
            }
        }

        dead = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = copy[i][j];
                if (!matrix[i][j]) {
                    dead = 0;
                }
            }
        }
    }

    printf("%d", time);

    return 0;
}
