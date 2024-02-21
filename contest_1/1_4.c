#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);

    int max_len = 1;
    int cur_len = 1;

    int previous_number;
    int current_number;
    scanf("%d", &current_number);

    for (int i = 1; i < n; ++i) {
        previous_number = current_number;
        scanf("%d", &current_number);

        if (previous_number < current_number) {
            ++cur_len;
        } else {
            if (cur_len > max_len) {
                max_len = cur_len;
            }
            cur_len = 1;
        }
    }

    if (cur_len > max_len) { ///< The case when the subsequence increases and ends
        max_len = cur_len;
    }

    printf("%d", max_len);

    return 0;
}
