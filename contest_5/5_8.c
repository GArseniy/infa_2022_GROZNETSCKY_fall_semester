#include <stdlib.h>
#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int abs_x = abs(x1 - x2), abs_y = abs(y1 - y2);

    int cnt = 0;

    if (n == 3) {
        if (x1 == x2 && y1 == y2) {
            cnt = 0;
        } else if ((x1 == 2 && y1 == 2) || (x2 == 2 && y2 == 2)) {
            cnt = -1;
        } else if ((abs_x + abs_y) == 1) {
            cnt = 3;
        } else if ((abs_x + abs_y) == 4) {
            cnt = 4;
        } else if ((abs_x + abs_y) == 3) {
            cnt = 1;
        } else if (abs_x * abs_y == 0) {
            if (x1 == 2 || y1 == 2 || x2 == 2 || y2 == 2) {
                cnt = 4;
            } else {
                cnt = 2;
            }
        } else {
            cnt = 2;
        }

    } else {
        while (abs_x >= 4 && abs_y >= 4) {
            ++cnt;
            if (abs_x < abs_y) {
                abs_x -= 1;
                abs_y -= 2;
            } else {
                abs_x -= 2;
                abs_y -= 1;
            }
        }

        if (abs_x > abs_y) {
            int tmp = abs_y;
            abs_y = abs_x;
            abs_x = tmp;
        }

        while (abs_y >= 6) {
            ++cnt;
            abs_y -= 2;

            if (abs_x >= 2) {
                abs_x -= 1;
            } else {
                abs_x += 1;
            }
        }

        if (abs_x == 1 && abs_y == 2) {
            cnt += 1;
        } else if ((abs_x == 1 && abs_y == 3) || (abs_x == 3 && abs_y == 3) || (abs_x == 0 && abs_y == 2) ||
                   (abs_x == 2 && abs_y == 4) || (abs_x == 0 && abs_y == 4)) {
            cnt += 2;
        } else if ((abs_x == 0 && abs_y == 1) || (abs_x == 0 && abs_y == 5) || (abs_x == 1 && abs_y == 4) ||
                   (abs_x == 2 && abs_y == 3) || (abs_x == 2 && abs_y == 5) || (abs_x == 3 && abs_y == 4)) {
            cnt += 3;
        } else if ((abs_x == 2 && abs_y == 2) || (abs_x == 1 && abs_y == 5) || (abs_x == 3 && abs_y == 5)) {
            cnt += 4;
        } else if (abs_x == 1 && abs_y == 1) {
            if ((x1 == 1 && y1 == 1) || (x2 == 1 && y2 == 1) || (x1 == 1 && y1 == n) || (x2 == 1 && y2 == n) ||
                (x1 == n && y1 == 1) || (x2 == n && y2 == 1) || (x1 == n && y1 == n) || (x2 == n && y2 == n)) {
                cnt += 4;
            } else {
                cnt += 2;
            }
        } else if (abs_x == 0 && abs_y == 3) {
            if (n == 4 &&
                ((x1 == 1 && y1 == 1) || (x2 == 1 && y2 == 1) || (x1 == 1 && y1 == n) || (x2 == 1 && y2 == n) ||
                 (x1 == n && y1 == 1) || (x2 == n && y2 == 1) || (x1 == n && y1 == n) || (x2 == n && y2 == n))) {
                cnt += 5;
            } else {
                cnt += 3;
            }
        }
    }

    printf("%d", cnt);

    return 0;
}
