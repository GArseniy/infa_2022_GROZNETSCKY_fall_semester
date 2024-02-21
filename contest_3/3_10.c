#include <stdio.h>


#define IS_NUMBER(x) ('0' <= (x) && (x) <= '9')


int read(void) {
    int c;
    while ((c = getchar()) == ' ');

    switch (c) {
        case '*':
            return read() * read();

        case '/':
            return read() / read();

        default: {
            int sign = (c == '-') ? (c = getchar(), -1) : 1;
            int ret = c - '0';

            while (c = getchar(), IS_NUMBER(c)) {
                ret *= 10;
                ret += c - '0';
            }

            return ret * sign;
        }
    }
}


int main(void) {
    printf("%d", read());

    return 0;
}
