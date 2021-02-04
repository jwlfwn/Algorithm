// 비재귀적 DFS, 제출일 : 2020-11-18
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int adjnode;
	struct node *next;
}node;

typedef struct vertex
{
	int visit;
	struct node *head;
}vertex;

void update_adjlist(vertex *arr, int k)
{
	node *cur, *prev, *newnode;
	cur = arr->head->next;
	prev = arr->head;

	while (cur != NULL)
	{
		if (cur->adjnode > k)
			break;
		cur = cur->next;
		prev = prev->next;
	}
	newnode = (node *)malloc(sizeof(node));
	newnode->adjnode = k;
	newnode->next = cur;
	prev->next = newnode;
	return;
}

void push(int s, int *Stack, int *topindex)
{
	*topindex += 1;
	Stack[*topindex] = s;
	return;
}

int pop(int *Stack, int *topindex)
{
	int save = *topindex;
	*topindex -= 1;
	return Stack[save];
}

void DFS(int s, vertex *arr)
{
	int Stack[1000], topindex = -1;
	int k;

	push(s, Stack, &topindex);
	arr[s].visit = 1;
	printf("%d\n", s);
	while (topindex != -1)
	{
		k = Stack[topindex];
		node *cur = arr[k].head->next;
		while (cur != NULL)
		{
			if (arr[cur->adjnode].visit == 0)
			{
				push(cur->adjnode, Stack, &topindex);
				arr[cur->adjnode].visit = 1;
				printf("%d\n", cur->adjnode);
				break;
			}
			cur = cur->next;
		}
		if (cur == NULL)
		{
			pop(Stack, &topindex);
		}
	}
	return;
}

void freeAll(vertex *arr, int n)
{
	node *cur, *prev;
	for (int i = 1; i <= n; i++)
	{
		cur = (arr + i)->head->next;
		prev = (arr + i)->head;
		while (cur != NULL)
		{
			free(prev);
			prev = cur;
			cur = cur->next;
		}
		free(prev);
	}
	return;
}

int main()
{
	vertex arr[101];
	int n, m, s;
	int a, b;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
	{
		arr[i].visit = 0;
		arr[i].head = (node *)malloc(sizeof(node));
		arr[i].head->next = NULL;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		update_adjlist(arr + a, b);
		update_adjlist(arr + b, a);
	}
	DFS(s, arr);
	freeAll(arr, n);
	return 0;
}