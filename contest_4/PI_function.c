#include <stdio.h>

const int STR_LEN = 1E4;

int pi_func(const char *str, const int *pi, int i) {
    if (!i) {
        return 0;
    }

    char c = str[i];

    while (pi[i - 1]) {
        if (c == str[pi[i - 1]]) {
            return pi[i - 1] + 1;
        }
        i = pi[i - 1];
    }

    return (c == str[0]);
}

int main(void) {
    char str[STR_LEN + 1];
    fgets(str, STR_LEN + 1, stdin);

    int pi[STR_LEN];
    int i = 0;

    while (str[i]) {
        pi[i] = pi_func(str, pi, i++);
    }

    return 0;
}