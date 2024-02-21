#include <stdio.h>

int get_bit(int n, int i){
    return (n >> i) & 1;
}

void set_bit(int* n, int i){
    *n |= (1 << i);
}

void unset_bit(int* n, int i){
    *n &= ~(1 << i);
}

void change_bit(int* n, int i){
    if (get_bit(*n, i)){
        unset_bit(n, i);
    }
    else{
        set_bit(n, i);
    }
}

int my_abs(int n){
    int bits_int_size;
    bits_int_size = sizeof(int) * 8;
    int sign;
    sign = get_bit(n, bits_int_size - 1);
    if (!sign){
        return n; // if sign is 0 ('+') than abs(n) = n
    }
    int i;
    i = 0;
    while (!get_bit(n, i)){
        ++i; //skip zeroes
    }
    ++i; //skip rightest one
    while (i < bits_int_size){
        change_bit(&n, i);
        ++i;
    }
    return n;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", my_abs(n));
    return 0;
}
