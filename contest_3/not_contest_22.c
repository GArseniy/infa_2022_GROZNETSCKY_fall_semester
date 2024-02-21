#include <stdio.h>

const int LEN = 80;

void incr(int *x, int n) {
    while (1) {
        if (x[n - 1] == 9) {
            x[n - 1] = 0;
            n--;
        } else {
            x[n - 1]++;
            break;
        }
    }
}

void sdvig(int *x, int n) {
    while (n >= 0) {
        x[n + 1] = x[n];
        n--;
    }

    x[0] = 0;
}

int is_schas(int *x, int n) {
    int s1 = 0, s2 = 0;

    for (int i = 0; i < n / 2; ++i) {
        s1 += x[i];
        s2 += x[n - i - 1];
    }

    return s1 == s2;
}

int main(void) {
    int str[LEN + 1];
    int c;
    int i = 0;

    while ((c = getchar()) != '\n') {
        str[i] = c - '0';
        i++;
    }

    if (i % 2) {
        sdvig(str, i);
        i++;
    }

    while (1) {
        if (is_schas(str, i)) {
            for (int j = (str[0] == 0); j < i; ++j) {
                printf("%d", str[j]);
            }
            break;
        } else {
            incr(str, i);
        }
    }

    return 0;
}
