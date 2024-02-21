#include <stdio.h>
#include <string.h>


const int STR_LEN = 1E6 + 1;


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
    char str_1[STR_LEN + 1], str_2[STR_LEN + 1];

    fgets(str_1, STR_LEN + 1, stdin);
    fgets(str_2, STR_LEN + 1, stdin);

    int len_1 = strlen(str_1), len_2 = strlen(str_2);

    if (str_1[len_1 - 1] == '\n'){
        str_1[--len_1] = '\0';
    }

    if (str_2[len_2 - 1] == '\n'){
        str_2[--len_2] = '\0';
    }

    int len = len_1 + 1 + len_2; ///< 1 extra space separates str1 and str2
    char concat[len + 1];
    memcpy(concat, str_1, sizeof(char) * len_1);
    concat[len_1] = ' ';
    concat[len_1 + 1] = '\0';
    strcat(concat, str_2);

    int pi[len];

    for (int i = 0; i < len; ++i) {
        pi[i] = pi_func(concat, pi, i);
    }

    printf("%d ", pi[len - 1]);

    memcpy(concat, str_2, sizeof(char) * len_2);
    concat[len_2] = ' ';
    concat[len_2 + 1] = '\0';
    strcat(concat, str_1);

    for (int i = 0; i < len; ++i) {
        pi[i] = pi_func(concat, pi, i);
    }

    printf("%d\n", pi[len - 1]);

    return 0;
}
