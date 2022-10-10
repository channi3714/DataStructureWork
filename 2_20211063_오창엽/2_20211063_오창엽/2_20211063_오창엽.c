#include <stdio.h>
#include <time.h>
#define MAX_TERMS 100

typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;

void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd);
void readPoly(FILE* fp, polynomial terms[], int* n);
void printPoly(polynomial terms[], int s, int f);
void attach(float coefficient, int exponent);

int main(void) {
	clock_t time_start = clock();
	int n = 0;
	FILE* afp = fopen("A.txt", "r");
	FILE* bfp = fopen("B.txt", "r");
	FILE* cfp = fopen("c.txt", "r");
	int starta, finisha, startb, finishb, startc, finishc;
	starta = n;
	readPoly(afp, terms, &n);
	finisha = n - 1;
	startb = n;
	readPoly(bfp, terms, &n);
	finishb = n - 1;
	startc = n;
	readPoly(cfp, terms, &n);
	finishc = n - 1;
	avail = n;
	int startd = 0;
	int finishd = 0;

	padd(starta, finisha, startb, finishb, &startd, &finishd);
	//printf("%d %d\n", n, avail);
	//printf("%d %d\n", startd, finishd);

	int s = startd, f = avail;
	//printPoly(terms, s, f);

	int starte = 0;
	int finishe = 0;
	padd(startd, finishd, startc, finishc, &starte, &finishe);

	s = starte;
	f = avail;

	printPoly(terms, s, f);

	fclose(afp);
	fclose(bfp);
	fclose(cfp);

	//clock_t time_stop = clock();

	printf("[Finished in %lfs]\n", ((double)(clock() - time_start)) / CLOCKS_PER_SEC);

	return 0;
}

void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	/* add A(x) and B(x) to obtain D(x) */
	int cmp;
	float coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch (compare(terms[starta].expon, terms[startb].expon)) {
		case -1: /* a expon < b expon */
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: /* equal exponents */
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1: /* a expon > b expon */
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	/* add in remaining terms of A(x) */
	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	/* add in remaining terms of B(x) */
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishd = avail - 1;
}


void readPoly(FILE* fp, polynomial terms[], int* n) {
	float cf;
	int ep;
	while (EOF != fscanf(fp, "%f %d", &cf, &ep)) {
		terms[*n].coef = cf;
		terms[*n].expon = ep;
		*n = *n + 1;
	}
}

void printPoly(polynomial terms[], int s, int f) {
	for (; s < f - 1; s++)
		printf("(%.0f, %d), ", terms[s].coef, terms[s].expon);
	printf("(%.0f, %d)\n", terms[f - 1].coef, terms[f - 1].expon);
	//printf("\n");
}

void attach(float coefficient, int exponent)
{
	/* add a new term to the polynomial */
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

int compare(int x, int y)
{
	/* compare x and y, return -1 for less than,
	0 for equal, 1 for greater */
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}