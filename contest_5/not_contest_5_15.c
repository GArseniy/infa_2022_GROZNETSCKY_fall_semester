#include <stdio.h>
#include <stdlib.h>


#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))


#define IS_EQUAL ((*r1 - '0' + *r2 - '0' + is_overflow) % 10 == *r3 - '0')
#define IS_MAYBE_EQUAL ((*r1 - '0' + *r2 - '0' + (maybe_overflow[0] != 0)) % 10 == *r3 - '0')


const int MAX_LEN = 200;


void read(char *x, int *l_x) {
    int c;

    while ((c = getchar()) != EOF && c != '\n' && c != '+' && c != '=') {
        x[(*l_x)++] = (char) c;
    }

    x[*l_x] = '\0';
}


char *is_correct(const char *a, const int l_a, const char *b, const int l_b, const char *c, const int l_c) {
    char ret_a[l_a], ret_b[l_b], ret_c[l_c];

    int min_len = min(l_a, min(l_b, l_c));

    int is_overflow = 0;
    char maybe_overflow[3] = {0};

    for (int i = 1; i <= min_len; ++i) {
        char s1 = a[l_a - i], s2 = b[l_b - i], s3 = c[l_c - i];

        char *r1 = &ret_a[l_a - i], *r2 = &ret_b[l_b - i], *r3 = &ret_c[l_c - i];

        *r1 = s1, *r2 = s2, *r3 = s3;

        int cnt = (s1 == '?') + (s2 == '?') + (s3 == '?');

        if (cnt == 0) {
            if (IS_EQUAL) {

            } else if (!is_overflow && IS_MAYBE_EQUAL) {
                *(++r1) = maybe_overflow[0];
                *(++r2) = maybe_overflow[1];
                *(++r3) = maybe_overflow[2];

            } else {
                return "No";
            }

            maybe_overflow[0] = 0;
            is_overflow = (s1 - '0' + s2 - '0' != s3 - '0');

        } else if (cnt == 1) {
            if (s1 == '?') {
                *r1 = (char) ('0' + (10 + s3 - s2 - is_overflow) % 10);
                if (s2 == s3) {

                }
            } else if (s2 == '?') {
                *r2 = (char) ('0' + (10 + s3 - s1 - is_overflow) % 10);

            } else {
                *r3 = (char) ('0' + (s1 + s2 + is_overflow) % 10);
            }


            is_overflow = !maybe_overflow[0] && (*r1 - '0' + *r2 - '0' + is_overflow != *r3 - '0');

        } else if (cnt == 2) {
            if ()
        }
    }

}


int main(void) {
    char *a = malloc(MAX_LEN * sizeof(int));
    int l_a = 0;
    read(a, &l_a);

    char *b = malloc(MAX_LEN * sizeof(int));
    int l_b = 0;
    read(b, &l_b);

    char *c = malloc(MAX_LEN * sizeof(int));
    int l_c = 0;
    read(c, &l_c);

    printf("%s", is_correct(a, l_a, b, l_b, c, l_c));

    return 0;
}
