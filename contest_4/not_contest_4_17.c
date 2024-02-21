#include <stdio.h>
#include <string.h>


const int MAX_LEN = (int) 2E6;


int pi_func(const char *str, const int *pi, int i) {
    if (!i) {
        return 0;
    }

    char c = str[i];

    while (pi[i - 1]) {
        if (c == str[pi[i - 1]]) {
            return pi[i - 1] + 1;
        }
        i = pi[i - 1];
    }

    return (c == str[0]);
}


int is_loop(const char *str, const int len) {
    int pi[len];
    int i = -1, max_sub = 0;

    while (str[++i]) {
        if ((pi[i] = pi_func(str, pi, i)) > max_sub) {
            max_sub = pi[i];
        }
        printf("%d ", pi[i]);
    }
    printf("\n%d %d\n", max_sub, len);

    if (max_sub != pi[max_sub * 2 - 1] || max_sub * 2 <= len/2) {
        return 0;
    }

    for (int j = max_sub * 2, k = 0; j < len; ++j, ++k) {
        if (str[j] != str[k]) {
            return 0;
        }
    }

    return 1;
}


int main(void) {
    char str[MAX_LEN + 1];
    scanf("%s", str);
    int len = (int) strlen(str);

    int numbers[len];
    int iter = 0;

    for (int i = 0; i < len; ++i) {
        int cnt = 0;
        while (str[i] == '0' && ++cnt && ++i);
        numbers[iter++] = cnt;

        cnt = 0;

        while (str[i] == '1' && ++cnt && ++i);
        numbers[iter++] = cnt;
    }

    if (!numbers[iter - 1]) {
        numbers[0] += numbers[iter - 2];
        numbers[iter - 2] = -1;
        iter -= 2;
    }

    int cnt_points = iter / 2;
    int points[cnt_points];
    for (int i = 0; i < cnt_points; points[i] = 2 * i, ++i);

    int loop = is_loop(str, len);
    printf("%d", loop);
    return 0;
    int cnt = 0;

    while (points[1] != -1) {
        int ret_points[cnt_points], ret_iter = 0;
        int max_len = 0;

        for (int i = 0; i < cnt_points; ++i) {
            if (numbers[points[i]] == max_len) {
                ret_points[ret_iter++] = (points[i] + 1) % cnt_points;
            } else if (numbers[points[i]] > max_len) {
                max_len = numbers[points[i]];
                ret_iter = 0;
                ret_points[ret_iter++] = (points[i] + 1) % cnt_points;
            }
        }

        if (loop) {
            int i = ret_points[0] - 1;

            for (int j = 0; j < iter; ++j) {
                for (int k = 0; k < numbers[i]; ++k) {
                    printf("%c", '0' + (i % 2));
                }

                i = (i + 1) % iter;
            }
        }

        for (int i = 0; i < ret_iter; ++i) {
            points[i] = ret_points[i];
        }

        points[ret_iter] = -1;
        cnt_points = ret_iter;

        if (points[1] != -1) {
            int min_len = len;
            ret_iter = 0;

            for (int i = 0; i < cnt_points; ++i) {
                if (numbers[points[i]] == min_len) {
                    ret_points[ret_iter++] = (points[i] + 1) % cnt_points;
                } else if (numbers[points[i]] < min_len) {
                    min_len = numbers[points[i]];
                    ret_iter = 0;
                    ret_points[ret_iter++] = (points[i] + 1) % cnt_points;
                }
            }
        }

        for (int i = 0; i < ret_iter; ++i) {
            points[i] = ret_points[i];
        }

        points[ret_iter] = -1;
        cnt_points = ret_iter;

        ++cnt;
    }

    int i = points[0] - cnt;

    for (int j = 0; j < iter; ++j) {
        for (int k = 0; k < numbers[i]; ++k) {
            printf("%c", '0' + (i % 2));
        }

        i = (i + 1) % iter;
    }

    return 0;
}