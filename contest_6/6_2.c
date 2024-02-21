#include <stdio.h>


int main(void) {
    FILE *input_f = fopen("input.txt", "r");

    int n, m;
    fscanf(input_f, "%d %d", &n, &m);
    int k;

    for (int i = 0; i < m; ++i) {
        fscanf(input_f, "%d", &k);
    }

    fclose(input_f);
    FILE *output_f = fopen("output.txt", "w");

    for (int i = 0; i < n; ++i) {
        fprintf(output_f, "%d ", (k + i - 1) % n + 1);
    }

    fclose(output_f);

    return 0;
}
