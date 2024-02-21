#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int MAX_LEN = 2000;
const int MAX_N = 120000;


#define IS_OPERATION(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/')
#define IS_NUMBER(c) ('0' <= (c) && (c) <= '9')


int search_boundary(char *str, int i, char **left_b) {
    if (!i || !IS_NUMBER(str[i - 1]) || !str[i + 1] || !IS_NUMBER(str[i + 1])) {
        return 0;
    }

    while (--i >= 0 && IS_NUMBER(str[i]));
    *left_b = str + i + 1;

    return 1;
}


int result(char *str, const int i, int *res, int *a, int *b) {
    char *left_b;

    if (!search_boundary(str, i, &left_b)) {
        return 0;
    }

    *a = atoi(left_b);
    *b = atoi(str + i + 1);

    switch (str[i]) {
        case '+':
            return abs(*res = *a + *b) <= MAX_N;
        case '-':
            return abs(*res = *a - *b) <= MAX_N;
        case '*':
            return abs(*res = *a * *b) <= MAX_N;
        case '/':
            return atoi(str + i + 1) && abs(*res = *a / *b) <= MAX_N;
        default:
            return 0;
    }
}


int main(void) {
    char str[MAX_LEN];
    scanf("%s", str);
    int len = strlen(str);

    int res, a, b;

    for (int i = 0; i < len; ++i) {
        if (IS_OPERATION(str[i]) && result(str, i, &res, &a, &b)) {
            printf("%d %c %d = %d\n", a, str[i], b, res);
        }
    }

    return 0;
}
