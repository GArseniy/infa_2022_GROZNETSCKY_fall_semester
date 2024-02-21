#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);
    int sum;
    sum = 0;
    for (int i=1; i <= n; ++i){
        for (int j=1; j <= n; ++j){
            sum += i*j;
        }
    }
    printf("%d", sum);
    return 0;
}