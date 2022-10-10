#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1001
int* sort(int U[], int size);
int main(void) {
	FILE* fp = fopen("lab1.data", "r");
	char c;
	int i, n, step = 10;
	int a[MAX_SIZE];
	clock_t time_start = clock();
	double duration;

	if (fp == NULL) {
		printf("파일열기 실패\n");
	}
	else {
		//printf("파일열기 성공\n");
	}

	int cnt = 0;
	//char array[100] = { '\0' };

	char* array = (char*)malloc(sizeof(char));

	while ((c = fgetc(fp)) != EOF) {
		if (c != '\n') {
			cnt++;
			realloc(array, sizeof(char) * cnt);
			array[cnt - 1] = c;
		}
	}

	int size = cnt;
	int* arr = (int*)malloc(sizeof(int) * size);

	printf("Input : ");

	for (i = 0; i < size; i++) {
		arr[i] = array[i] - '0';
		printf("%d ", arr[i]);
	}

	printf("\n");
	int* S = sort(arr, size);
	printf("Sorted : ");
	for (i = 0; i < size; i++) {
		printf("%d ", S[i]);
	}

	printf("\n");

	printf("    n   repetitions time\n");

	for (n = 0; n <= 100; n += step) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;

			for (i = 0; i < n; i++) {
				a[i] = n - 1;
			}
			sort(a, n);
		} while (clock() - start < 100);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d  %9d   %f\n", n, repetitions, duration);
	}

	fclose(fp);
	int total_time = ((double)(clock() - time_start)) / CLOCKS_PER_SEC;
	printf("[Finished in %ds]\n", total_time);
	return 0;
}
int* sort(int U[], int size) {
	int i, j;
	int* S = (int*)malloc(sizeof(int) * size);
	S[0] = U[0];
	for (i = 1; i < size; i++) {
		for (j = i - 1; j >= 0 && U[i] < S[j]; j--) {
			S[j + 1] = S[j];
		}
		U[0] = U[i];
		U[i] = -1;
		S[j + 1] = U[0];
	}
	/*
	printf("Sorted : ");
	for (i = 0; i < size; i++) {
		printf("%d ", S[i]);
	}

	printf("\n");
	*/
	return S;
}