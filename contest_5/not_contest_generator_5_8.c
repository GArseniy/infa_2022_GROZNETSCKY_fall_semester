#include <stdlib.h>
#include <stdio.h>


#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))


int check(int x, int y, int n, int **field) {
    if (x >= 0 && y >= 0 && x < n && y < n && field[x][y] == -1) {
        return 1;
    }

    return 0;
}

int horse(int **field, int n, int xk, int yk, int data) {
    int ok = 1;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (field[x][y] == data) {
                for (int i = -2; i <= 2; i++) {
                    for (int j = -2; j <= 2; j++) {
                        if (i * i != j * j && i != 0 && j != 0) {
                            if (x + i == xk && y + j == yk) {
                                return data + 1;

                            }
                            if (check(x + i, y + j, n, field)) {
                                field[x + i][y + j] = data + 1;
                                ok = 0;
                            }
                        }
                    }
                }
                field[x][y] = -2;
            }
        }
    }
    if (ok) {
        return -1;
    }

    return 0;
}


int main(void) {
    while (1) {
        int n = 3 + rand()%100;
        int x1 = 1 + rand() % n, y1 = 1 + rand() % n, x2 = 1 + rand() % n, y2 = 1 + rand() % n;

        int cnt = 0;

        if (n == 3) {
            int abs_x = abs(x1 - x2), abs_y = abs(y1 - y2);

            if ((x1 == 2 && y1 == 2) && (x2 == 2 && y2 == 2)) {
                cnt = 0;
            } else if ((x1 == 2 && y1 == 2) || (x2 == 2 && y2 == 2)) {
                cnt = -1;
            } else if ((abs_x + abs_y) == 0) {
                cnt = 0;
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
            int abs_x = abs(x1 - x2), abs_y = abs(y1 - y2);

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

        ///<

        int cor_res = 0;
        while (1) {
            int **field = (int **) malloc(n * sizeof(int *));

            for (int i = 0; i < n; i++) {
                field[i] = (int *) malloc(n * sizeof(int));
                for (int j = 0; j < n; j++) {
                    field[i][j] = -1;
                }
            }

            int xn = x1, yn = y1, xk = x2, yk = y2;
            if (xn == xk && yn == yk) {
                cor_res = 0;
                break;
            }

            xk--;
            yk--;
            field[--xn][--yn] = 0;

            int cnt_vania = 0;

            while (1) {
                if (cor_res = horse(field, n, xk, yk, cnt_vania++)) {
                    break;
                }
            }
            break;
        }

        if (cor_res != cnt) {
            printf("%d %d %d %d %d: %d != %d", n, x1, y1, x2, y2, cor_res, cnt);
            break;
        }
    }

    return 0;
}
