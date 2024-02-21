#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int STR_LEN = (int) 1E6 + 1;


int prefix_f(const char *str, const int *pi, int i) {
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


int count_prefix(const char *str) {
    int len = (int) strlen(str);
    int prefix[len];

    for (int i = 0; i < len; ++i) {
        prefix[i] = prefix_f(str, prefix, i);
    }

    return prefix[len - 1];
}


char *concat(const char *str_1, const char *str_2) {
    int len_1 = (int) strlen(str_1);
    int len_2 = (int) strlen(str_2);

    int len = len_1 + len_2 + 1;

    char *str_cat = malloc(sizeof(char) * (len + 1));
    memcpy(str_cat, str_1, sizeof(char) * len_1);

    str_cat[len_1] = ' ';
    str_cat[len_1 + 1] = '\0';

    return strcat(str_cat, str_2);
}


void carry_out(const char *str_1, const char *str_2) {
    char *str_cat = concat(str_1, str_2);

    printf("%d\n", count_prefix(str_cat));

    free(str_cat);
}


int main(void) {
    char str_1[STR_LEN + 1], str_2[STR_LEN + 1];

    scanf("%s %s", str_1, str_2);

    carry_out(str_1, str_2);
    carry_out(str_2, str_1);

    return 0;
}
