#include <stdio.h>


#define MAX_SIZE 2000


int max_prefix_func(char * str, int start, int len) {
    int pi[len - start];
    pi[0] = 0;

    if (len - start == 1) {
        return 0;
    }

    int j = 0, i = 1;

    while (i < len - start) {
        if (str[i + start] == str[j + start]) {
            pi[i] = j + 1;
            i++;
            j++;
        }
        else {
            if (j == 0) {
                pi[i] = 0;
                i++;
            }
            else {
                j = pi[j - 1];
            }
        }
    }

    int max = 0;

    for (int i = 0; i < len - start; i++) {
        if (pi[i] > max) {
            max = pi[i];
        }
    }

    return max;

}


int main(void) {
    char str[MAX_SIZE + 1];

    char c;
    int len = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        str[len] = c;
        len++;
    }

    int cnt = 1;

    for (int i = len - 1; i >= 0; i--) {
        cnt += len - i - max_prefix_func(str, i, len);
    }

    printf("%d", cnt);

    return 0;
}
