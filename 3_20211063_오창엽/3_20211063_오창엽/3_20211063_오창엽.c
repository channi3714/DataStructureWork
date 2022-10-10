#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int row, column, value;
} Term;
#define MAX_TERMS 1024
void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);
int main() {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE* fp = fopen("./A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);
	fp = fopen("./B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);
	matrixAdd(a, b, c);
	/*printMatrix(a);
	printf("\n");
	printMatrix(b);*/
	printMatrix(c);
	return 0;
}

void readMatrix(FILE* fp, Term a[]) {
	int n, m, val, cnt = 1, ncnt = -1, mcnt = 0;
	char c;

	fscanf(fp, "%d %d\n", & n, &m);
	a[0].row = n;
	a[0].column = m;

	while (EOF != fscanf(fp, " %d ", &val)) {
		if (mcnt % m == 0) {
			mcnt = 0;
			ncnt++;
		}
		//if (val != 0) {
			a[cnt].row = ncnt;
			a[cnt].column = mcnt;
			a[cnt].value = val;
			cnt++;
		//}
		mcnt++;
	}
	a[0].value = cnt - 1;
}

void printMatrix(Term a[]) {
	for (int i = 0; i <= a[0].value; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}

void matrixAdd(Term a[], Term b[], Term c[]) {
	int n = a[0].row, m = a[0].column, size = a[0].value;
	int i = 1, cnt = 0;

	c[cnt].row = n;
	c[cnt].column = m;
	cnt++;

	while (i < size) {
		if (a[i].value != 0 || b[i].value != 0) {
			c[cnt].row = a[i].row;
			c[cnt].column = a[i].column;
			c[cnt].value = a[i].value + b[i].value;
			//printf("%d %d %d\n", c[cnt].row, c[cnt].column, c[cnt].value);
			cnt++;
		}
		i++;
	}
	c[0].value = cnt - 1;
	
}