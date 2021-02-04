#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void update_adjacency_matrix(int a, int b, int w, int arr[][7])
{
	if (a < 1 || a > 6 || b < 1 || b > 6)
	{
		printf("-1\n");
		return;
	}

	if (w == 0)
	{
		arr[a][b] = -1;
		arr[b][a] = -1;
	}
	else
	{
		arr[a][b] = w;
		arr[b][a] = w;
	}
	return;
}

int main()
{
	int arr[7][7];
	int a, b, w;
	int node_num;
	char key;

	for (int i = 1; i < 7; i++)
	{
		for (int j = 1; j < 7; j++)
			arr[i][j] = -1;
	}

	arr[1][2] = 1;
	arr[1][3] = 1;
	arr[1][4] = 1;
	arr[1][6] = 2;
	arr[2][1] = 1;
	arr[2][3] = 1;
	arr[3][1] = 1;
	arr[3][2] = 1;
	arr[3][5] = 4;
	arr[4][1] = 1;
	arr[5][3] = 4;
	arr[5][5] = 4;
	arr[5][6] = 3;
	arr[6][1] = 2;
	arr[6][5] = 3;

	while (1)
	{
		scanf("%c", &key);
		switch (key)
		{
		case 'a':
			scanf("%d", &node_num); getchar();
			if (node_num < 1 || node_num>6)
			{
				printf("-1\n");
				continue;
			}
			for (int i = 1; i < 7; i++)
			{
				if (arr[node_num][i] != -1)
					printf(" %d %d", i, arr[node_num][i]);
			}
			printf("\n");
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			update_adjacency_matrix(a, b, w, arr);
			break;
		case'q':
			exit(-1);
			break;
		}
	}
	return 0;
}