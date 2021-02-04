#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int getNextBucket(int M, int v, int i)
{
	return (v + i) % M;
}

int insertkey(int *hash, int M, int x)
{
	int v = x % M;
	for (int i = 0; i < M; i++)
	{
		int b = getNextBucket(M, v, i);
		if (hash[b] == 0)
		{
			hash[b] = x;
			return b;
		}
		printf("C");
	}
}

int findElement(int *hash, int M, int x)
{
	int v = x % M;
	for (int i = 0; i < M; i++)
	{
		int b = getNextBucket(M, v, i);
		if (hash[b] == 0)
			return -1;
		else if (x == hash[b])
			return b;
		else
			continue;
	}
	return -1;
}

int main()
{
	int M, N;
	int *hash, key;
	char str;
	scanf("%d %d", &M, &N); getchar();
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
			printf("%d\n", insertkey(hash, M, key));
			break;
		case 's':
			scanf("%d", &key); getchar();
			int k = findElement(hash, M, key);
			if (k == -1)
				printf("%d\n", k);
			else
				printf("%d %d\n", k, key);
			break;
		case 'e':
			exit(-1);
			break;
		}
	}
	free(hash);
	return 0;
}