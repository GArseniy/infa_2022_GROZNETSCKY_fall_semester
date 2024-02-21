#include <stdio.h>

const int STR_LEN = 1E2 + 1;
const char VOWELS[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U', 'y', 'Y'};
const int CNT_VOWELS = 12;

int is_vowel(const char c) {
    for (int i = 0; i < CNT_VOWELS; ++i) {
        if (c == VOWELS[i]) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    int n;
    scanf("%d", &n);

    int lens[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", lens + i);
    }

    char str[STR_LEN + 1];

    for (int i = 0; i < n; ++i) {
        int c;
        int len = 0;
        fflush(stdin);
        while ((c = getchar()) != '\n' && c != EOF) {
            str[len++] = c;
        }
        str[len] = '\0';

        int is_previous_vowel = 0;
        for (int j = 0; j < len; ++j) {
            if (!is_vowel(str[j])) {
                is_previous_vowel = 0;
                continue;
            }

            if (is_previous_vowel) {
                continue;
            }

            --lens[i];
            is_previous_vowel = 1;
        }

        if (!lens[i]) {
            printf("%s\n", str);
        }
    }

    return 0;
}