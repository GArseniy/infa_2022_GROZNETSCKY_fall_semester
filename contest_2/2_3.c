#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);
    int arr_1[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr_1[i]);
    }

    int m;
    scanf("%d", &m);
    int arr_2[m];

    for (int j = 0; j < m; ++j) {
        scanf("%d", &arr_2[j]);
    }

    int arr_3[n + m];

    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {
        arr_3[k++] = arr_1[i++];
        arr_3[k++] = arr_2[j++];
    }
    while (i < n) {
        arr_3[k++] = arr_1[i++];
    }
    while (j < m) {
        arr_3[k++] = arr_2[j++];
    }

    for (int l = 0; l < n + m; ++l) {
        printf("%d ", arr_3[l]);
    }

    return 0;
}
