#include <stdio.h>


const int MAX_WEIGHT = 1E6;


int main(void) {
    int weight;
    scanf("%d", &weight);

    int cnt = 0;
    int pow = 1;
    int scales = weight;

    while (weight > 0) {
        cnt += (weight % 3) != 0;

        if (weight % 3 == 2) {
            scales += pow;
            weight += 3;
        }

        weight /= 3;
        pow *= 3;
    }

    if (scales > MAX_WEIGHT) {
        cnt = -1;
    }

    printf("%d", cnt);

    return 0;
}
