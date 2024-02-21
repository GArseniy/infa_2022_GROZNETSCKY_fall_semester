#include <stdio.h>
#include <math.h>
#include <limits.h>


unsigned my_f(unsigned x) {
    return x * (unsigned) sqrt(x);
}


int main(void) {
    unsigned long long y;
    scanf("%llu", &y);


    unsigned previous_x = 0;

    for (unsigned k=0; k != 100;++k) { // FIXME
        for (unsigned x = sqrtl(x)*x, stopper = sqrt(x)*x + x + 1; x < stopper; ++x) {

        }
    }
    return 0;
}