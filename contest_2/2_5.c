#include <stdio.h>
#include <math.h>


const int DIM_COORS = 3;


int main(void) {
    int n;
    scanf("%d", &n);

    double balls[n][DIM_COORS + 1];

    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf %lf", &balls[i][0], &balls[i][1], &balls[i][2], &balls[i][3]);
    }

    int result = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = sqrt(
                    pow(balls[i][0] - balls[j][0], 2) +
                    pow(balls[i][1] - balls[j][1], 2) +
                    pow(balls[i][2] - balls[j][2], 2)
            );

            if (distance <= balls[i][3] + balls[j][3]) {
                result = 1;
                break;
            }
        }

        if (result) {
            break;
        }
    }

    if (result) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
