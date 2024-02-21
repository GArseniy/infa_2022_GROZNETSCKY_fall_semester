#include <stdio.h>
#include <stdlib.h>

int check(int x, int y, int n, int **field) {
	if (x >= 0 && y >= 0 && x < n && y < n && field[x][y] == -1) {
		return 1;
	}

	return 0;
}

int horse(int **field, int n, int xk, int yk, int data) {
	int ok = 1;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (field[x][y] == data) {
				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						if (i * i != j * j && i != 0 && j != 0) {
							if (x + i == xk && y + j == yk) {
								printf("%d\n", data + 1);

								return 1;

							}
							if (check(x + i, y + j, n, field)) {
								field[x + i][y + j] = data + 1;
								ok = 0;
							}
						}
					}
				}
				field[x][y] = -2;
			}
		}
	}
	if (ok) {
		printf("-1\n");

		return 1;
	}

	return 0;
}

int main(void) {

	int n;
	scanf("%d", &n);
	int **field = (int **) malloc(n * sizeof(int *));

	for (int i = 0; i < n; i++) {
		field[i] = (int *) malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			field[i][j] = -1;
		}
	}

	int xn, yn, xk, yk;
	scanf("%d%d%d%d", &xn, &yn, &xk, &yk);

	if (xn == xk && yn == yk) {
		printf("0\n");

		return 0;
	}

	xk--;
	yk--;
	field[--xn][--yn] = 0;

	int cnt = 0;

	while (1) {
		if (horse(field, n, xk, yk, cnt++)) {
			break;
		}
	}

	return 0;
}