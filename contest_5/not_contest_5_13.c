///< NOT CONTEST!!!


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


const int MAX_CNT = 1100000;


typedef struct Point {
    int x, y, val;
} point;


void swiftUp(point *heap, int i) {
    for (; i > 0; i /= 2) {
        if (heap[i / 2].val > heap[i].val) {
            point tmp = heap[i];
            heap[i] = heap[i / 2];
            heap[i / 2] = tmp;
        } else {
            return;
        }
    }
}

void swiftDown(point *heap, int *n, int i) {
    while (i * 2 <= (*n)) {
        if (i * 2 + 1 <= (*n)) {
            if (heap[i * 2].val < heap[i * 2 + 1].val) {
                if (heap[i * 2].val < heap[i].val) {
                    point tmp = heap[i];
                    heap[i] = heap[i * 2];
                    heap[i * 2] = tmp;
                    i *= 2;
                } else {
                    return;
                }
            } else {
                if (heap[i * 2 + 1].val < heap[i].val) {
                    point tmp = heap[i];
                    heap[i] = heap[i * 2 + 1];
                    heap[i * 2 + 1] = tmp;
                    i = i * 2 + 1;
                } else {
                    return;
                }
            }
        } else {
            if (heap[i * 2].val < heap[i].val) {
                point tmp = heap[i];
                heap[i] = heap[i * 2];
                heap[i * 2] = tmp;
                i *= 2;
            } else {
                return;
            }
        }
    }
}


void add(point *heap, int *n, point p) {
    heap[++(*n)] = p;
    swiftUp(heap, *n);
}


void extractMin(point *heap, int *n) {
    heap[0] = heap[(*n)--];
    swiftDown(heap, n, 0);
}


int main(void) {
    int n, m, n0, m0, n1, m1;
    scanf("%d %d %d %d %d %d", &n, &m, &n0, &m0, &n1, &m1);

    short **g = malloc(n * sizeof(short *));

    for (int i = 0; i < n; ++i) {
        g[i] = malloc(m * sizeof(short));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%hd", &g[i][j]);
        }
    }

    short **used = malloc(n * sizeof(short *));

    for (int i = 0; i < n; ++i) {
        used[i] = calloc(m, sizeof(short));
    }

    int **values = malloc(n * sizeof(int *));

    for (int i = 0; i < n; ++i) {
        values[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; ++j) {
            values[i][j] = INT_MAX;
        }
    }

    values[n0][m0] = 0;

    point heap[MAX_CNT + 1];
    int cnt = 0;
    point tmp = {.val = 0, .x = n0, .y = m0};
    add(heap, &cnt, tmp);

    while (!used[n1][m1]) {
        int min_i = heap[1].x, min_j = heap[1].y;
        extractMin(heap, &cnt);
        used[min_i][min_j] = 1;

        if (min_i > 0 &&
            values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i - 1][min_j]) < values[min_i - 1][min_j]) {
            values[min_i - 1][min_j] = values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i - 1][min_j]);
            point tmp = {.val = values[min_i - 1][min_j], .x = min_i - 1, .y = min_j};
            add(heap, &cnt, tmp);
        }
        if (min_i + 1 < n &&
            values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i + 1][min_j]) < values[min_i + 1][min_j]) {
            values[min_i + 1][min_j] = values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i + 1][min_j]);
            point tmp = {.val = values[min_i + 1][min_j], .x = min_i + 1, .y = min_j};
            add(heap, &cnt, tmp);
        }
        if (min_j > 0 &&
            values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i][min_j - 1]) < values[min_i][min_j - 1]) {
            values[min_i][min_j - 1] = values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i][min_j - 1]);
            point tmp = {.val = values[min_i][min_j - 1], .x = min_i, .y = min_j - 1};
            add(heap, &cnt, tmp);
        }
        if (min_j + 1 < m &&
            values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i][min_j + 1]) < values[min_i][min_j + 1]) {
            values[min_i][min_j + 1] = values[min_i][min_j] + abs(g[min_i][min_j] - g[min_i][min_j + 1]);
            point tmp = {.val = values[min_i][min_j + 1], .x = min_i, .y = min_j + 1};
            add(heap, &cnt, tmp);
        }
    }

    printf("%d", values[n1][m1]);

    for (int i = 0; i < n; ++i) {
        free(g[i]);
    }
    free(g);

    return 0;
}
