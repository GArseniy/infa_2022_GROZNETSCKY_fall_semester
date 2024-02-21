#include <stdio.h>


const int MAX_LEN = 255;


int main(void) {
    char str[MAX_LEN + 1];
    int c;
    int len = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        str[len++] = (char) c;
    }

    str[len] = '\0';

    for (int i = 0; i < len; ++i) {
        int cnt = 0;

        for (int j = 0; j < i; ++j) {
            if (str[j] == 'A') {
                cnt += (j % 2) ? 1 : -1;
            }
        }

        for (int j = i + 1; j < len; ++j) {
            if (str[j] == 'A') {
                cnt += (j % 2) ? -1 : 1;
            }
        }

        if (!cnt) {
            printf("%d ", i + 1);
        }
    }
    return 0;
}
