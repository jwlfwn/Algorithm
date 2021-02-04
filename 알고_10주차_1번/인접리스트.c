#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node  // 인접리스트
{
	int adjnode;
	int weight;
	struct node *next;
}node;

typedef struct vertex
{
	int elem;
	struct node *head;
}vertex;

node* getnode(int adjver, int weight)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->adjnode = adjver;
	newnode->weight = weight;
	newnode->next = NULL;
	return newnode;
}

void print_adjver(int node_num, vertex *arr)
{
	if (node_num < 1 || node_num > 6)
	{
		printf("-1\n");
		return;
	}
	
	node *cur = arr->head;

	while (cur->next != NULL)
	{
		printf(" %d %d", cur->next->adjnode, cur->next->weight);
		cur = cur->next;
	}
	printf("\n");
	return;
}

void update_adjlist(int a, int b, int w, vertex *arr)
{
	node *cur = NULL, *prev = NULL;

	if (a < 1 || a > 6 || b < 1 || b > 6)
	{
		printf("-1\n");
		return;
	}

	if (w == 0)
	{
		cur = (arr + a)->head->next;
		prev = (arr + a)->head;
		while (cur != NULL && cur->adjnode != b)
		{
			cur = cur->next;
			prev = prev->next;
		}
		if (cur == NULL)
			prev->next = NULL;
		else
		{
			prev->next = cur->next;
			cur->next = NULL;
			free(cur);
		}
		if (a != b)
		{
			cur = (arr + b)->head->next;
			prev = (arr + b)->head;
			while (cur != NULL && cur->adjnode != a)
			{
				cur = cur->next;
				prev = prev->next;
			}
			if (cur == NULL)
				prev->next = NULL;
			else
			{
				prev->next = cur->next;
				cur->next = NULL;
				free(cur);
			}
		}
	}
	else
	{
		cur = (arr + a)->head->next;
		prev = (arr + a)->head;
		while (cur != NULL && cur->adjnode != b && cur->adjnode < b)
		{
			cur = cur->next;
			prev = prev->next;
		}
		if (cur == NULL)
			prev->next = getnode(b, w);
		else if (cur->adjnode == b)
			cur->weight = w;
		else
		{
			node *newnode = getnode(b, w);
			newnode->next = cur;
			prev->next = newnode;
		}
		if (a != b)
		{
			cur = (arr + b)->head->next;
			prev = (arr + b)->head;
			while (cur != NULL && cur->adjnode != a && cur->adjnode < a)
			{
				cur = cur->next;
				prev = prev->next;
			}
			if (cur == NULL)
				prev->next = getnode(a, w);
			else if (cur->adjnode == a)
				cur->weight = w;
			else
			{
				node *newnode = getnode(a, w);
				newnode->next = cur;
				prev->next = newnode;
			}
		}
	}
	return;
}

void freeAll(vertex *arr)
{
	node *cur, *prev;
	for (int i = 1; i < 7; i++)
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
	vertex arr[7];
	node *cur;
	int node_num;
	int a, b, w;
	char key;

	for (int i = 1; i < 7; i++)
	{
		arr[i].elem = i;
		arr[i].head = (node *)malloc(sizeof(node));
		arr[i].head->next = NULL;
	}

	cur = arr[1].head;
	cur->next = getnode(2, 1); cur = cur->next;
	cur->next = getnode(3, 1); cur = cur->next;
	cur->next = getnode(4, 1); cur = cur->next;
	cur->next = getnode(6, 2);

	cur = arr[2].head;
	cur->next = getnode(1, 1); cur = cur->next;
	cur->next = getnode(3, 1); cur = cur->next;

	cur = arr[3].head;
	cur->next = getnode(1, 1); cur = cur->next;
	cur->next = getnode(2, 1); cur = cur->next;
	cur->next = getnode(5, 4); cur = cur->next;

	cur = arr[4].head;
	cur->next = getnode(1, 1); cur = cur->next;

	cur = arr[5].head;
	cur->next = getnode(3, 4); cur = cur->next;
	cur->next = getnode(5, 4); cur = cur->next;
	cur->next = getnode(6, 3); cur = cur->next;

	cur = arr[6].head;
	cur->next = getnode(1, 2); cur = cur->next;
	cur->next = getnode(5, 3); cur = cur->next;

	while (1)
	{
		scanf("%c", &key);
		switch (key)
		{
		case 'a':
			scanf("%d", &node_num);
			print_adjver(node_num, arr + node_num);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			update_adjlist(a, b, w, arr);
			break;
		case 'q':
			exit(-1);
			break;
		}
	}
	freeAll(arr);
	return 0;
}