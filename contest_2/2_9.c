#include <stdio.h>


int main(void) {
    int n;
    scanf("%d", &n);
    int polynomial[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", &polynomial[i]);
    }

    int m;
    scanf("%d", &m);
    int args[m];

    for (int i = 0; i < m; ++i) {
        scanf("%d", &args[i]);
    }

    for (int i = m - 1; i >= 0; --i) {
        int result = 0, pow = 1;

        for (int j = 0; j < n; ++j) {
            result += polynomial[j] * pow;
            pow *= args[i];
        }

        printf("%d ", result);
    }

    return 0;
}
