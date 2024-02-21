#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *pi_func(const char *str, const int len) {
    int *pi = malloc(len * sizeof(int));
    pi[0] = 0;

    for (int i = 1, j = 1; i < len; ++i, j = i) {
        while (pi[j - 1]) {
            if (str[pi[j - 1]] == str[i]) {
                pi[i] = pi[j - 1] + 1;
                break;
            }

            j = pi[j - 1];
        }
    }

    return pi;
}


int is_loop(const char *str, const int len, const int len_sub) {

}