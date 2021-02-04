#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void Bellman_Ford(int arr[][101], int *d, int n, int s)
{
	int cnt = 0;
	d[s] = 0;
	while (cnt < n - 1)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (d[i] != INT_MAX && arr[i][j] != 21)
				{
					if (d[i] + arr[i][j] < d[j])
						d[j] = d[i] + arr[i][j];
				}
			}
		}
		cnt++;
	}
	return;
}

int main()
{
	int n, m, s;
	int a, b, w;
	int arr[101][101], *d;
	scanf("%d %d %d", &n, &m, &s);
	d = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1; i <= n; i++)
	{
		d[i] = INT_MAX;
		for (int j = 1; j <= n; j++)
			arr[i][j] = 21;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &a, &b, &w);
		arr[a][b] = w;  // 방향가중그래프
	}
	Bellman_Ford(arr, d, n, s);
	for (int i = 1; i <= n; i++)
	{
		if (i != s && d[i] != INT_MAX)
			printf("%d %d\n", i, d[i]);
	}
	free(d);
	return 0;
}