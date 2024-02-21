#include <stdio.h>
#include <stdlib.h>


void read(int ***m, int *dim) {
    scanf("%d", dim);
    *m = malloc(*dim * sizeof(long *));

    for (int i = 0; i < *dim; ++i) {
        (*m)[i] = malloc(*dim * sizeof(long));
    }

    for (int i = 0; i < *dim; ++i) {
        for (int j = 0; j < *dim; ++j) {
            scanf("%d", &(*m)[i][j]);
        }
    }
}


long trace(int **m, int dim) {
    long trace = 0;

    for (int i = 0; i < dim; ++i) {
        trace += m[i][i];
    }

    return trace;
}


void write(int **m, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            printf("%d ", m[i][j]);
        }

        printf("\n");
    }
}


void delete(int **m, int dim) {
    for (int j = 0; j < dim; ++j) {
        free(m[j]);
    }

    free(m);
}


int main(void) {
    int n;
    scanf("%d", &n);

    int max_dim;
    int **max_matrix;

    read(&max_matrix, &max_dim);
    long max_trace = trace(max_matrix, max_dim);

    for (int i = 1; i < n; ++i) {
        int dim;
        int **matrix;

        read(&matrix, &dim);
        long tr = trace(matrix, dim);

        if (tr > max_trace) {
            max_trace = tr;

            int tmp_d = dim;
            dim = max_dim;
            max_dim = tmp_d;

            int **tmp_m = matrix;
            matrix = max_matrix;
            max_matrix = tmp_m;
        }

        delete(matrix, dim);
    }

    write(max_matrix, max_dim);
    delete(max_matrix, max_dim);

    return 0;
}
