#include <stdio.h>

int main(void){
    int n;
    scanf("%d", &n);
    int numbers[n];
    int i_of_max, i_of_min;
    int max, min;
    max = 0;
    min = 1000000000;
    i_of_max = 0;
    i_of_min = 0;
    for (int i=0; i < n; ++i){
        scanf("%d", &numbers[i]);
        if (numbers[i] > max){
            max = numbers[i];
            i_of_max = i;
        }
        if (numbers[i] < min){
            min = numbers[i];
            i_of_min = i;
        }
    }
    int i1, i2;
    if (i_of_min > i_of_max){
        i1 = i_of_max;
        i2 = i_of_min;
    } else{
        i2 = i_of_max;
        i1 = i_of_min;
    }
    for (int i=0; i < n; ++i){
        if ((i1 <= i) && (i <= i2)){
            printf("%d ", numbers[i1 + i2 - i]);
        } else{
            printf("%d ", numbers[i]);
        }
    }
    return 0;
}