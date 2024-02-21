#include <stdio.h>


int main(void) {
    unsigned int x = 5000000;
    x ^= 63;

    printf("%u\n", x);

    return 0;
}
