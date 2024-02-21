#include <stdio.h>
#include <string.h>


const int MAX_LEN = (int) 2E6;


int search(const char *str, const int len, int *points, const char c, const int is_max) {
    int size_points = 0;
    while (points[size_points] != -1) {
        ++size_points;
    }

    int ret_points[size_points];
    int ret_iter = 0;

    int iter = -1, extra_len = 0;
    int is_break = 0;

    if (is_max == -1) {
        extra_len = MAX_LEN;
    }

    while (++iter < size_points) {
        int cur_len = 0;
        while (str[(points[iter] + cur_len) % len] == c) {
            ++cur_len;
            if (cur_len > 2 * len) {
                ret_iter = 0;
                ret_points[ret_iter++] = 0;
                is_break = 1;
                break;
            }
        }

        if (is_break) {
            break;
        }

        if (cur_len == extra_len) {
            ret_points[ret_iter++] = (points[iter] + cur_len) % len;
        } else if (cur_len * is_max > extra_len * is_max) {
            ret_iter = 0;
            ret_points[ret_iter++] = (points[iter] + cur_len) % len;
            extra_len = cur_len;
        }
    }
    ret_points[ret_iter] = -1;

    iter = 0;
    while (ret_points[iter] != -1) {
        points[iter] = ret_points[iter];
        ++iter;
    }
    points[iter] = -1;

    return extra_len;
}


int main(void) {
    char str[MAX_LEN + 1];
    scanf("%s", str);
    int len = strlen(str);

    int points[len + 1];
    for (int i = 0; i < len; ++i) {
        points[i] = i;
    }
    points[len] = -1;

    int l = 0;
    int n = 1;

    while (points[1] != -1) {
        if (n % 2) {
            l += search(str, len, points, '0', 1);
        } else {
            l += search(str, len, points, '1', -1);
        }
        ++n;
        if (n > len) {
            l = 0;
            break;
        }
    }

    for (int j = 0; j < len; ++j) {
        printf("%c", str[(len + points[0] - l + j) % len]);
    }

    return 0;
}
