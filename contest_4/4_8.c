#include <stdio.h>


const int STR_LEN = 101;
const int MAX_N = 999;
const int MIN_N = 100;


int my_atoi(char *s) {
    int res = 0;

    while (*s != '\0') {
        res = 10 * res + *s - '0';
        ++s;
    }

    return res;
}


int main(void) {
    char str[STR_LEN + 1];
    int len = 0, c;

    while ((c = getchar()) != '\n' && c != EOF) {
        str[len++] = (char) c;
    }

    str[len] = '\0';

    int cnt[MAX_N + 1];
    for (int i = 0; i <= MAX_N; cnt[i++] = 0);

    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            for (int k = j + 1; k < len; ++k) {
                char n[] = {str[i], str[j], str[k], '\0'};
                cnt[my_atoi(n)] = 1;
            }
        }
    }

    int res = 0;

    for (int i = MIN_N; i <= MAX_N; ++i) {
        res += cnt[i];
    }

    printf("%d", res);

    return 0;
}
