#include <stdio.h>

int read(void) {
    int ret_number = 0;

    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (c >= '0' && c <= '9') {
            ret_number *= 10;
            ret_number += c - '0';

        } else if (c == '*') {
            return read() * read();

        } else if (c == '/') {
            return read() / read();

        } else if (ret_number) {
            return ret_number;
        }
    }

    return ret_number;
}

int main(void) {
    printf("%d", read());

    return 0;
}
