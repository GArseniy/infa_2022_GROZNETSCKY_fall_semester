#include <stdio.h>
#include <stdlib.h>


#define IS_PRIME(x) ((x) == 2 || (x) == 3 || (x) == 5 || (x) == 7)
#define IS_DIVIDER(x) ((x) == 0 || (x) == 2 || (x) == 4 || (x) == 5 || (x) == 6 || (x) == 8)


const int SIZE_OF_ARR = 100;
const int BASE_SYSTEM = 10;


int is_prime(const int x) {
    for (int i = 2; i * i < x; ++i) {
        if (!(x % i)) {
            return 0;
        }
    }

    return 1;
}


int *hyper_prime(int n) {
    int *ret = malloc(SIZE_OF_ARR * sizeof(int));
    int iter = 0;

    if (n == 1) {
        for (int i = 0; i < BASE_SYSTEM; ++i) {
            if (IS_PRIME(i)) {
                ret[iter++] = i;
            }
        }

    } else {
        int *prev_primes = hyper_prime(n - 1);

        for (int p = 0; prev_primes[p]; ++p) {
            for (int i = 0; i < BASE_SYSTEM; ++i) {
                if (!IS_DIVIDER(i)) {
                    int number = prev_primes[p] * BASE_SYSTEM + i;

                    if (is_prime(number)) {
                        ret[iter++] = number;
                    }
                }
            }
        }

        free(prev_primes);
    }
    ret[iter] = 0;

    return ret;
}


void print(int *arr) {
    for (int p = 0; arr[p]; ++p) {
        printf("%d ", arr[p]);
    }
}


int main(void) {
    int n;
    scanf("%d", &n);

    int *hyper_primes = hyper_prime(n);
    print(hyper_primes);
    free(hyper_primes);

    return 0;
}
