#include <stdio.h>
#include <string.h>
#define CRT_SECURE_NO_WARNINGS
#define max_string_size 100
#define max_pattern_size 100

int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];

int nfind(char* string, char* pat, int* cnt);
int pmatch(char* string, char* pat, int* cnt);
void fail(char* pat, int* cnt);

int main(void) {
	int cnt = 0;
	int nfd, kmp;

	scanf("%s", string);
	scanf("%s", pat);

	nfd = nfind(string, pat, &cnt);

	if (nfd != -1) {
		printf("nfind:  YES %d\n", cnt);
	}
	else {
		printf("nfind:  No %d\n", cnt);
	}
	
	cnt = 0;

	fail(pat, &cnt);

	kmp = pmatch(string, pat, &cnt);

	if (kmp != -1) {
		printf("kmp:    YES %d\n", cnt);
	}
	else {
		printf("kmp:    No %d\n", cnt);
	}

	return 0;
}

int nfind(char* string, char* pat, int* cnt)
{
	/* match the last character of the pattern first, and then match from the beginning */
	int i = 0, j = 0, start = 0;
	*cnt = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		*cnt += 1;
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++) {
				*cnt += 1;
			}
		if (j == lastp) return start; /* successful */
	}
	return -1;
}

int pmatch(char* string, char* pat, int* cnt)
{
	/* Knuth, Morris, Pratt string matching algorithm */
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		*cnt += 1;
		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

void fail(char* pat, int* cnt)
{
	/* compute the pattern¡¯s failure function */
	int i, j, n = strlen(pat);
	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		*cnt += 1;
		while ((pat[j] != pat[i + 1]) && (i >= 0)) {
			i = failure[i];
			*cnt += 1;
		}
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}