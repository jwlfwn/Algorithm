#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Priority_Queue
{
	int u;  // u, v�� �ش� ����ġ�� ���� ����
	int v;  
	int weight;  // ����ġ
}Queue;

void swap(Queue *a, Queue *b)  // ����ü Queue ��°�� ��ȯ
{
	Queue temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void downheap(Queue *H, int i, int m_copy)
{
	int l, r, smaller;
	l = 2 * i;
	r = 2 * i + 1;
	if (l > m_copy)
		return;
	smaller = l;
	if (r <= m_copy)
		if (H[smaller].weight > H[r].weight)
			smaller = r;
	if (H[i].weight <= H[smaller].weight)
		return;
	swap(&H[i], &H[smaller]);
	downheap(H, smaller, m_copy);
}

int *removeMin(Queue *H, int *m_copy)
{
	int *save = (int*)malloc(sizeof(int) * 2);
	save[0] = H[1].u;
	save[1] = H[1].v;
	H[1] = H[*m_copy];
	(*m_copy)--;
	downheap(H, 1, *m_copy);
	return save;
}

void union_Sack(int a, int b, int n, int *Sack)
{
	int k1 = Sack[a], k2 = Sack[b];  // Sack[i]�� ���߿� ���� �ٲ�������Ƿ� �̸� �����ϰ� ��
	for (int i = 1; i <= n; i++)
		if (Sack[i] == k1)
			Sack[i] = k2;
	return;
}
// Sack[2]=1 �̸� 2�������� ����1�� �ִٴ� ��
void Kruskal(Queue *H, int arr[][101], int n, int m, int *mst)
{
	int *Sack = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1; i <= n; i++)
		Sack[i] = i; 
	int flag = 1, m_copy = m;  // �������� ������ ����ŭ ���Ƿ� m_copy�� ������ ���� ��������
	while (flag < n)
	{
		int *vertex = removeMin(H, &m_copy);
		int a = vertex[0], b = vertex[1];
		if (Sack[a] != Sack[b])
		{
			mst[flag] = arr[a][b];
			union_Sack(a, b, n, Sack);
			flag++;
		}
	}
	free(Sack);
	return;
}

void upHeap(Queue *H, int i)
{
	if (i == 1)
		return;
	if (H[i / 2].weight <= H[i].weight)
		return;
	swap(&H[i / 2], &H[i]);
	upHeap(H, i / 2);
}

void printMST(int *mst, int n)
{
	int sum = 0;
	for (int i = 1; i < n; i++)
	{
		sum += mst[i];
		printf(" %d", mst[i]);
	}
	printf("\n%d\n", sum);
	return;
}

int main()
{
	int arr[101][101];
	int n, m;
	int a, b, w;
	int *mst;
	Queue *H;
	scanf("%d %d", &n, &m);
	H = (Queue*)malloc(sizeof(Queue)*(m + 1));
	mst = (int*)malloc(sizeof(int)*n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			arr[i][j] = 0;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d %d %d", &a, &b, &w);
		arr[a][b] = w;
		arr[b][a] = w;
		H[i].u = a;
		H[i].v = b;
		H[i].weight = w;
		upHeap(H, i);  // ����ġ�� �ּ��� ����
	}
	Kruskal(H, arr, n, m, mst);
	printMST(mst, n);
	free(H);
	free(mst);
	return 0;
}