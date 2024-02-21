#include <stdio.h>


const int SIZE_OF_N = 2;
const int SIZE_OF_X = 4;
const int SIZE_OF_TRACE = 8;
const int BYTE = 8;


int read(int size, void *stream) {
    int x = 0;

    unsigned char buffer[size];
    fread(buffer, sizeof(unsigned char), size, stream);

    for (int i = 0; i < size; ++i) {
        x |= (int) buffer[i] << BYTE * (size - 1 - i);
    }

    return x;
}


void write(long long trace, void *stream) {
    unsigned char buffer[SIZE_OF_TRACE];

    for (int i = 0; i < SIZE_OF_TRACE; ++i) {
        buffer[SIZE_OF_TRACE - 1 - i] = (int) (trace >> BYTE * i);
    }

    fwrite(buffer, sizeof(unsigned char), SIZE_OF_TRACE, stream);
}


int main(void) {
    FILE *matrix_in = fopen("matrix.in", "rb");

    int n = read(SIZE_OF_N, matrix_in);
    long long trace = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = read(SIZE_OF_X, matrix_in);

            if (i == j) {
                trace += x;
            }
        }
    }

    fclose(matrix_in);

    FILE *trace_out = fopen("trace.out", "wb");
    write(trace, trace_out);
    fclose(trace_out);

    return 0;
}
