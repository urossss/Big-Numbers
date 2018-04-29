#include <stdio.h>
#include "funkcije.h"

int main() {
	char a[MAX], b[MAX], c[2 * MAX], d[MAX];
	int na, nb, nc, nd;

	while (load(a, &na) && load(b, &nb)) {
		printf("a = "); write(a, na);
		printf("b = "); write(b, nb);

		add(a, na, b, nb, c, &nc);
		printf("a + b = "); write(c, nc);

		if (compare(a, na, b, nb) >= 0) {
			sub(a, na, b, nb, c, &nc);
			printf("a - b = "); write(c, nc);
		}
		else {
			sub(b, nb, a, na, c, &nc);
			printf("b - a = "); write(c, nc);
		}

		mul(a, na, b, nb, c, &nc);
		printf("a * b = "); write(c, nc);

		if (!zero(b, nb)) {
			div(a, na, b, nb, c, &nc, d, &nd);
			printf("a / b = "); write(c, nc);
			printf("a %% b = "); write(d, nd);
		}
	}

}