#include <stdio.h>


int main(void) {
    unsigned int a11, a12, a21, a22, b1, b2;
    scanf("%u %u %u %u %u %u", &a11, &a12, &a21, &a22, &b1, &b2);

    unsigned int x;
    x = 0xffffffff ^ b2 ^ b1 ^ (b1 & b2) ^ (a22 & b2) ^ (a22 & b1 & b2) ^ a21 ^ (a21 & b1) ^ (a21 & a22) ^
        (a21 & a22 & b1) ^ (a12 & b1) ^ (a12 & b1 & b2) ^ (a12 & a22 & b2) ^ (a12 & a22 & b1) ^ (a12 & a22 & b1 & b2) ^
        (a12 & a21 & b1) ^ (a12 & a21 & a22) ^ (a12 & a21 & a22 & b1) ^ a11 ^ (a11 & b2) ^ (a11 & a22 & b2) ^
        (a11 & a21) ^ (a11 & a21 & a22) ^ (a11 & a12) ^ (a11 & a12 & b2) ^ (a11 & a12 & a22) ^ (a11 & a12 & a22 & b2) ^
        (a11 & a12 & a21) ^ (a11 & a12 & a21 & a22);

    a11 &= x;
    a21 &= x;

    unsigned int y;
    y = 0xffffffff ^ b2 ^ b1 ^ (b1 & b2) ^ a22 ^ (a22 & b1) ^ a21 ^ (a21 & b1) ^ a12 ^ (a12 & b2) ^ (a12 & a22) ^
        (a12 & a21) ^ a11 ^ (a11 & b2) ^ (a11 & a22) ^ (a11 & a21);

    if (((a11 ^ (a12 & y)) == b1) && ((a21 ^ (a22 & y)) == b2)) {
        printf("Yes\n%u %u\n", x, y);
    } else {
        printf("No\n");
    }

    return 0;
}
