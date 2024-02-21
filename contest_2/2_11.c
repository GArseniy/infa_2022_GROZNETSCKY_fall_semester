#include <stdio.h>


#define SIZE 8


int main(void) {
    int table[SIZE * SIZE] = {0};

    char a, b;

    while ((a = getchar()) != EOF && (b = getchar()) != EOF) {
        a -= 'a';
        b -= '1';

        table[a * SIZE + b] = 1;

        if (a > 0) {
            if (b > 0) {
                table[(a - 1) * SIZE + b - 1] = 1;
            }

            table[(a - 1) * SIZE + b] = 1;

            if (b < SIZE - 1) {
                table[(a - 1) * SIZE + b + 1] = 1;
            }
        }

        if (a < SIZE - 1) {
            if (b > 0) {
                table[(a + 1) * SIZE + b - 1] = 1;
            }

            table[(a + 1) * SIZE + b] = 1;

            if (b < SIZE - 1) {
                table[(a + 1) * SIZE + b + 1] = 1;
            }
        }

        if (b > 0) {
            if (a > 0) {
                table[(a - 1) * SIZE + b - 1] = 1;
            }

            table[a * SIZE + b - 1] = 1;

            if (a < SIZE - 1) {
                table[(a + 1) * SIZE + b - 1] = 1;
            }
        }

        if (b < SIZE - 1) {
            if (a > 0) {
                table[(a - 1) * SIZE + b + 1] = 1;
            }

            table[a * SIZE + b + 1] = 1;

            if (a < SIZE - 1) {
                table[(a + 1) * SIZE + b + 1] = 1;
            }
        }
    }

    int cnt = SIZE * SIZE;

    for (int i = 0; i < SIZE * SIZE; ++i) {
        cnt -= table[i];
    }

    printf("%d", cnt);

    return 0;
}
