#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int A, B, M, n, i = 0;
	char *K;

	scanf("%d %d %d", &A, &B, &n);
	getchar();
	K = (char *)malloc(sizeof(char)*n);
	scanf("%s", K);

	while (i < n)
	{
		M = (A + B) / 2;
		if (K[i] == 'Y')
			A = M + 1;
		else
			B = M;
		i++;
	}
	printf("%d", A);

	return 0;
}
