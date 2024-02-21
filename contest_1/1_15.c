#include <stdio.h>


#define CONVEX(p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y) {\
    int l13_a1 = p3_y - p1_y, l13_a2 = p1_x - p3_x, l13_b = p1_x * p3_y - p3_x * p1_y;\
    int l24_a1 = p4_y - p2_y, l24_a2 = p2_x - p4_x, l24_b = p2_x * p4_y - p4_x * p2_y;\
    int det_A = l13_a1 * l24_a2 - l13_a2 * l24_a1; \
    \
    if (det_A) { \
        int inter_x = (l13_b * l24_a2 - l13_a2 * l24_b) / det_A;\
        int inter_y = (l13_a1 * l24_b - l13_b * l24_a1) / det_A;\
        \
        result *=\
        ((p1_x < p3_x) ? p1_x : p3_x) <= inter_x && inter_x <= ((p1_x > p3_x) ? p1_x : p3_x) &&\
        ((p1_y < p3_y) ? p1_y : p3_y) <= inter_y && inter_y <= ((p1_y > p3_y) ? p1_y : p3_y) &&\
        ((p2_x < p4_x) ? p2_x : p4_x) <= inter_x && inter_x <= ((p2_x > p4_x) ? p2_x : p4_x) &&\
        ((p2_y < p4_y) ? p2_y : p4_y) <= inter_y && inter_y <= ((p2_y > p4_y) ? p2_y : p4_y);\
        } else {\
        result = 0;\
    }\
}


int main(void) {
    int n;
    scanf("%d", &n);
    int result = 1;

    if (n >= 4) {
        int start_x1, start_y1, start_x2, start_y2, start_x3, start_y3;

        scanf("%d %d", &start_x1, &start_y1);
        scanf("%d %d", &start_x2, &start_y2);
        scanf("%d %d", &start_x3, &start_y3);

        int x2 = start_x1, y2 = start_y1;
        int x3 = start_x2, y3 = start_y2;
        int x4 = start_x3, y4 = start_y3;

        for (int i = 4; i <= n; ++i) {
            int x1 = x2, y1 = y2;
            x2 = x3, y2 = y3;
            x3 = x4, y3 = y4;
            scanf("%d %d", &x4, &y4);

            CONVEX(x1, y1, x2, y2, x3, y3, x4, y4)

            if (!result) {
                break;
            }
        }

        CONVEX(x2, y2, x3, y3, x4, y4, start_x1, start_y1)
        CONVEX(x3, y3, x4, y4, start_x1, start_y1, start_x2, start_y2)
        CONVEX(x4, y4, start_x1, start_y1, start_x2, start_y2, start_x3, start_y3)
    }

    if (result) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}
