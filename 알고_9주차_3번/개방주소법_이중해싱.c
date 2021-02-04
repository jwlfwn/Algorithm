#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int getNextBucket(int M, int v, int i, int q, int x)
{
	return (v + i * (q - (x%q))) % M;
}

int insertkey(int *hash, int M, int x, int q)
{
	int v = x % M;
	for (int i = 0; i < M; i++)
	{
		int b = getNextBucket(M, v, i, q, x);
		if (hash[b] == 0)
		{
			hash[b] = x;
			return b;
		}
		printf("C");
	}
}

int findElement(int *hash, int M, int x, int q)
{
	int v = x % M;
	for (int i = 0; i < M; i++)
	{
		int b = getNextBucket(M, v, i, q, x);
		if (hash[b] == 0)
			return -1;
		else if (x == hash[b])
			return b;
		else
			continue;
	}
	return -1;
}

void print(int *hash, int M)
{
	for (int i = 0; i < M; i++)
		printf(" %d", hash[i]);
	printf("\n");
}

int main()
{
	int M, N, q;
	int *hash, key;
	char str;
	scanf("%d %d %d", &M, &N, &q); getchar();
	hash = (int*)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++)
		hash[i] = 0;
	while (1)
	{
		scanf("%c", &str);
		switch (str)
		{
		case 'i':
			scanf("%d", &key); getchar();
			printf("%d\n", insertkey(hash, M, key, q));
			break;
		case 's':
			scanf("%d", &key); getchar();
			int k = findElement(hash, M, key, q);
			if (k == -1)
				printf("%d\n", k);
			else
				printf("%d %d\n", k, key);
			break;
		case 'p':
			print(hash, M);
			break;
		case 'e':
			print(hash, M);
			exit(-1);
			break;
		}
	}
	free(hash);
	return 0;
}