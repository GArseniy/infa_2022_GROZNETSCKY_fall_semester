#include <stdio.h>


int is_symmetrical(void) {
    static int is_first_point = 1;

    int x1, y1;
    scanf("%d %d", &x1, &y1);

    if (!x1) {
        return (is_first_point) ? (is_first_point = 0, is_symmetrical()) : 1;
    }

    if (is_symmetrical()) {
        int x2, y2;
        scanf("%d %d", &x2, &y2);

        return (x1 == -x2 && y1 == y2);
    }

    return 0;
}


int main(void) {
    int n;
    scanf("%d", &n);

    printf(is_symmetrical() ? "Yes" : "No");

    return 0;
}
