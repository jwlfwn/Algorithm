#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct node  // ��������Ʈ
{
	int adjnode;
	int weight;
	struct node *next;
}node;

typedef struct vertex  // ����
{
	int elem;
	struct node *head;
}vertex;

typedef struct label
{
	int *d;  // �������������� �ִܰŸ�
	int *locator;  // �������� ��ġ (= �����ε���)
	int *isQueue;  // �켱����ť�� �����ϴ���
}label;

node *getnode()
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->next = NULL;
	return newnode;
}

void addnode(vertex *arr, int node_num, int w)
{
	node *cur = arr->head;
	node *newnode = getnode();
	newnode->adjnode = node_num;
	newnode->weight = w;
	newnode->next = cur->next;
	cur->next = newnode;
	return;
}

void Init_label(label *label, int n)
{
	label->d = (int *)malloc(sizeof(int)*(n + 1));
	label->locator = (int *)malloc(sizeof(int)*(n + 1));
	label->isQueue = (int*)malloc(sizeof(int)*(n + 1));
	return;
}

void swap(label *label, int *H, int p, int c)
{
	int temp;
	label->locator[H[p]] = c;
	label->locator[H[c]] = p;
	temp = H[p];
	H[p] = H[c];
	H[c] = temp;
	return;
}

void upHeap(label *label, int *H, int s)
{
	if (s == 1)
		return;
	if (label->d[H[s / 2]] <= label->d[H[s]])
		return;
	swap(label, H, s / 2, s);
	upHeap(label, H, s / 2);
}

void downHeap(label *label, int *H, int i, int n_copy)
{
	int l, r, smaller;
	l = 2 * i; 
	r = 2 * i + 1;
	if (l > n_copy)
		return;
	smaller = l;
	if (r <= n_copy)
		if (label->d[H[smaller]] > label->d[H[r]])
			smaller = r;
	if (label->d[H[i]] <= label->d[H[smaller]])
		return;
	swap(label, H, i, smaller);
	downHeap(label, H, smaller, n_copy);
}

int removeMin(label *label, int *H, int *n_copy)
{
	int save = H[1];
	label->locator[H[1]] = '\0';
	label->isQueue[H[1]] = 0;  // ť���� ����
	H[1] = H[*n_copy];
	label->locator[H[1]] = 1;
	(*n_copy)--;
	downHeap(label, H, 1, *n_copy);
	return save;
}

void DijkstraShortestPath(label *label,vertex *arr, int n, int s)
{
	int n_copy = n;
	int *H = (int*)malloc(sizeof(int)*(n + 1));
	for (int i = 1; i <= n; i++)
	{
		label->d[i] = INT_MAX;
		label->locator[i] = i;
		label->isQueue[i] = 1;
		H[i] = i;
	}
	label->d[s] = 0;
	upHeap(label, H, s);
	while (n_copy >= 1)  // ť�� ������� ��������
	{
		int u = removeMin(label, H, &n_copy);
		node *cur = (arr + u)->head->next;
		while (cur != NULL)
		{
			int k = cur->adjnode, t = cur->weight;
			if (label->isQueue[k] == 1)  // ť�� �����ϸ�
			{
				if (label->d[u] + t < label->d[k])
				{
					label->d[k] = label->d[u] + t;
					upHeap(label, H, label->locator[k]);
				}
			}
			cur = cur->next;
		}
	}
	free(H);
	return;
}

void freeAll(label *label)
{
	free(label->d);
	free(label->locator);
	free(label->isQueue);
	return;
}

int main()
{
	int n, m, s;
	int a, b, w;
	vertex arr[101];  // arr[1]~arr[100]
	label label;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)  // �������ֱ�, ��������Ʈ �ʱ�ȭ
	{
		arr[i].elem = 1;
		arr[i].head = getnode();
	}
	for (int i = 1; i <= m; i++)  // ��������Ʈ ����
	{
		scanf("%d %d %d", &a, &b, &w);
		addnode(arr + a, b, w);
		addnode(arr + b, a, w);
	}
	Init_label(&label, n);
	DijkstraShortestPath(&label, arr, n, s);
	for (int i = 1; i <= n; i++)
		if (i != s && label.d[i] != INT_MAX)
			printf("%d %d\n", i, label.d[i]);
	freeAll(&label);
	return 0;
}