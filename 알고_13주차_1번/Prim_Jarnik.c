#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct label
{
	int *d;
	int *locator;
	int *isQueue;  // �켱���� ť�� ������ �ִ���
}label;

void swap(int *H, label *label, int parent, int child)
{
	int temp;
	label->locator[H[parent]] = child;
	label->locator[H[child]] = parent;
	temp = H[parent];
	H[parent] = H[child];
	H[child] = temp;
	return;
}

void upHeap(int *H, label *label, int locate)
{
	if (locate == 1)
		return;
	if (label->d[H[locate / 2]] <= label->d[H[locate]])
		return;
	swap(H, label, locate / 2, locate);
	upHeap(H, label, locate / 2);
}

void downheap(int *H, label *label, int i, int n_copy)
{
	int l, r, smaller;
	l = 2 * i;
	r = 2 * i + 1;

	if (l > n_copy)
		return;
	smaller = l;
	if (r <= n_copy)
	{
		if (label->d[H[smaller]] > label->d[H[r]])
			smaller = r;
	}
	if (label->d[H[i]] <= label->d[H[smaller]])
		return;
	swap(H, label, i, smaller);
	downheap(H, label, smaller, n_copy);
}

int removeMin(int *H, label *label, int *n_copy, int n, int *mst)
{
	int save = H[1];
	label->locator[H[1]] = '\0'; // ������ ������ ��ġ�� ���� ���� 
	label->isQueue[H[1]] = 0;  // �켱����ť���� ������
	H[1] = H[*n_copy];
	label->locator[H[1]] = 1;
	(*n_copy)--;
	downheap(H, label, 1, *n_copy);
	mst[n - *n_copy] = save;
	return save;
}

void Prim_JarnikMST(int arr[][101], label *label, int n, int *mst)
{
	int *H = (int*)malloc(sizeof(int)*(n + 1));
	int n_copy = n;  // ������ ���� ����
	for (int i = 1; i <= n; i++)
	{
		label->d[i] = INT_MAX;  // ���Ѵ�
		label->locator[i] = i;  // ����i�� �켱����ť������ ��ġ(= H�� �ε���)
		label->isQueue[i] = 1;  // ���� ������ ��� �켱����ť�� ����
		H[i] = i;
	}
	label->d[1] = 0;
	int u = 0, locate = 0;
	while (n_copy >= 1)  // �켱����ť�� ������� ��������
	{
		u = removeMin(H, label, &n_copy, n, mst);
		for (int i = 1; i <= n; i++)
		{
			if (arr[u][i] != 0)
			{
				if (label->isQueue[i] == 1 && arr[u][i] < label->d[i])
				{
					label->d[i] = arr[u][i];
					locate = label->locator[i];
					upHeap(H, label, locate);
				}
			}
		}
	}
	free(H);
	return;
}

void Init_label(label *label, int n)
{
	label->d = (int*)malloc(sizeof(int)*(n + 1));
	label->locator = (int*)malloc(sizeof(int)*(n + 1));
	label->isQueue = (int*)malloc(sizeof(int)*(n + 1));
	return;
}

void printMST(label label, int *mst, int n)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
		printf(" %d", mst[i]);
	printf("\n");
	for (int i = 2; i <= n; i++)
		sum += label.d[i];
	printf("%d\n", sum);
	return;
}

void freeAll(int *mst, label *label)
{
	free(mst);
	free(label->d);
	free(label->locator);
	free(label->isQueue);
	return;
}

int main()
{
	int arr[101][101];
	int n, m;
	int a, b, w;
	int *mst;
	label label;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			arr[i][j] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &w);
		arr[a][b] = w;
		arr[b][a] = w;
	}
	Init_label(&label, n);
	mst = (int*)malloc(sizeof(int)*(n + 1));
	Prim_JarnikMST(arr, &label, n, mst);
	printMST(label, mst, n);
	freeAll(mst, &label);
	return 0;
}