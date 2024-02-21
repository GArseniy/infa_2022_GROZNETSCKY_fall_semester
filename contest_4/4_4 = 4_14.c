#include <stdio.h>
#include <stdlib.h>


const int MAX_LEN = (int) 1E6;


int main(void) {
    int *diff = malloc((MAX_LEN + 1) * sizeof(int));
    char *str = malloc((MAX_LEN + 1) * sizeof(char));
    int c, iter = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (!iter) {
            diff[iter] = (c == 'A');

        } else {
            diff[iter] = diff[iter - 1];

            if (c == 'A') {
                diff[iter] += (iter % 2) ? -1 : 1;
            }
        }

        str[iter++] = (char) c;
    }

    for (int i = 0, last = diff[iter - 1]; i < iter; ++i) {
        if ((str[i] == 'A' && last == 2 * diff[i] + ((i % 2) ? 1 : -1)) ||
            (str[i] == 'B' && last == 2 * diff[i])) {
            printf("%d ", i + 1);
        }
    }

    free(diff);
    free(str);

    return 0;
}
