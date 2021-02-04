#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int isEmpty(int front, int rear)
{	
	if (front == rear)
		return 1;
	else
		return 0;
}

void Enqueue(int s, int *Queue, int *rear)
{
	*rear = (*rear + 1) % 101;
	Queue[*rear] = s;
	return;
}

int Dequeue(int *Queue, int *front)
{
	*front = (*front + 1) % 101;
	return Queue[*front];
}

void BFS(int s, int arr[][101], int *visit, int n)
{
	int Queue[101], front = 0, rear = 0;
	int k;

	Enqueue(s, Queue, &rear);
	visit[s] = 1;
	while (!isEmpty(front, rear))
	{
		k = Dequeue(Queue, &front);
		printf("%d\n", k);
		for (int i = 1; i <= n; i++)
		{
			if (arr[k][i] == 1 && visit[i] == 0)
			{
				Enqueue(i, Queue, &rear);
				visit[i] = 1;
			}
		}
	}
	return;
}

int main()
{
	int arr[101][101];
	int visit[101];
	int n, m, s;
	int a, b;

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
	{
		visit[i] = 0;
		for (int j = 1; j <= n; j++)
			arr[i][j] = 0;
	}
	
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		arr[a][b] = 1;
		arr[b][a] = 1;
	}

	BFS(s, arr, visit, n);
	return 0;
}