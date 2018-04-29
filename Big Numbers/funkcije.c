#include <stdio.h>
#include <ctype.h>
#include "funkcije.h"

int load(char a[], int *n) {
	char broj[MAX + 1];
	int i, j;
	scanf("%s", broj);
	for (i = 0; broj[i]; i++)
		if (!isdigit(broj[i])) return 0;
	*n = i;
	for (i = *n - 1, j = 0; i >= 0; a[i--] = broj[j++] - '0');	// cuvamo broj od cifara najmanje tezine
	while (*n > 1 && a[*n - 1] == 0) (*n)--;					// vodece nule ne racunamo, osim poslednje ako je broj 0
	return 1;
}

void write(char a[], int n) {
	for (int i = n - 1; i >= 0; i--) {
		putchar(a[i] + '0');
		if (i % 3 == 0) putchar(' ');
	}
	putchar('\n');
}

int zero(char a[], int n) {
	return n == 1 && a[0] == 0;
}

int compare(char a[], int na, char b[], int nb) {
	if (na != nb) return na - nb;
	int i;
	for (i = na - 1; i > 0 && a[i] == b[i]; i--);
	return a[i] - b[i];
}

void add(char a[], int na, char b[], int nb, char c[], int *nc) {
	int i, p, r;
	for (i = p = 0; i < na || i < nb; i++) {
		r = p;
		if (i < na) r += a[i];
		if (i < nb) r += b[i];
		if (r >= 10) {
			p = 1;
			r -= 10;
		}
		else p = 0;
		c[i] = r;
	}
	if (p) c[i++] = p;
	*nc = i;
}

void sub(char a[], int na, char b[], int nb, char c[], int *nc) {
	int i, p, r;
	for (i = p = 0; i < na; i++) {
		r = p + a[i];
		if (i < nb) r -= b[i];
		if (r < 0) {
			p = -1;
			r += 10;
		}
		else p = 0;
		c[i] = r;
	}
	for (i = na - 1; i > 0 && c[i] == 0; i--);
	*nc = i + 1;
}

void mul(char a[], int na, char b[], int nb, char c[], int * nc) {
	if (!zero(a, na) && !zero(b, nb)) {
		int i, j, p, r;
		*nc = na + nb;
		for (i = 0; i < *nc; c[i++] = 0);
		for (i = 0; i < na; i++)
			for (j = p = 0; j < nb || p; j++) {
				r = c[i + j] + p;
				if (j < nb) r += a[i] * b[j];
				c[i + j] = r % 10;
				p = r / 10;
			}
		if (c[*nc - 1] == 0) (*nc)--;
	}
	else {
		c[0] = 0;
		*nc = 1;
	}
}

void div(char a[], int na, char b[], int nb, char c[], int *nc, char d[], int *nd) {
	int i, j, nn;
	for (i = 0; i < na; i++) d[i] = a[i];
	*nd = na;
	nn = na - nb + 1;
	if (compare(a, na, b, nb) >= 0) {
		*nc = nn; *nd = nb;
		for (i = *nc - 1, j = na - nb; i >= 0; i--, j--, (*nd)++) {
			c[i] = 0;
			while (compare(d + j, *nd, b, nb) >= 0) {
				sub(d + j, *nd, b, nb, d + j, nd);
				c[i]++;
			}
		}
		if (*nc > 1 && c[*nc - 1] == 0) (*nc)--;
		while (*nd > 1 && d[*nd - 1] == 0) (*nd)--;
	}
	else {
		*nc = 1; c[0] = 0;
	}
}
