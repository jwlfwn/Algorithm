#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key;
	struct node *next;
}node;

node *getnode(int x)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->key = x;
	newnode->next = NULL;
	return newnode;
}

void insertkey(node *hash, int M, int x)
{
	int v = x % M;
	node *newnode = getnode(x);
	newnode->next = hash[v].next;
	hash[v].next = newnode;
	return;
}

int findElement(node *hash, int M, int x)
{
	int v = x % M;
	int flag = 0, index = 1;
	node *cur = hash[v].next;
	while (cur != NULL)
	{
		if (cur->key == x)
		{
			flag++;
			break;
		}
		index++;
		cur = cur->next;
	}
	if (flag)
		return index;
	else
		return 0;
}

int removeElement(node *hash, int M, int x)
{
	int v = x % M;
	int flag = 0, index = 1;
	node *cur = hash + v, *del = NULL;
	while (cur->next != NULL)
	{
		if (cur->next->key == x)
		{
			del = cur->next;
			if (del->next == NULL)
				cur->next = NULL;
			else
				cur->next = del->next;
			flag++;
			break;
		}
		index++;
		cur = cur->next;
	}
	free(del);
	if (flag)
		return index;
	else
		return 0;
}

void print(node *hash, int M)
{
	node *cur;
	for (int i = 0; i < M; i++)
	{
		cur = hash[i].next;
		while (cur != NULL)
		{
			printf(" %d", cur->key);
			cur = cur->next;
		}
	}
	printf("\n");
	return;
}

void freeAll(node *hash, int M)
{
	node *cur, *del;
	for (int i = 0; i < M; i++)
	{
		cur = (hash + i)->next;
		if (cur != NULL)
		{
			del = cur;
			cur = cur->next;
			free(del);
		}
	}
	free(hash);
	return;
}

int main()
{
	int M, key;
	char str;
	scanf("%d", &M); getchar();
	node *hash = (node*)malloc(sizeof(node)*M);
	for (int i = 0; i < M; i++)
		hash[i].next = NULL;
	while (1)
	{
		scanf("%c", &str);
		switch (str)
		{
		case 'i':
			scanf("%d", &key); getchar();
			insertkey(hash, M, key);
			break;
		case 's':
			scanf("%d", &key); getchar();
			printf("%d\n", findElement(hash, M, key));
			break;
		case 'd':
			scanf("%d", &key); getchar();
			printf("%d\n", removeElement(hash, M, key));
			break;
		case 'p':
			print(hash, M);
			break;
		case 'e':
			exit(-1);
			break;
		}
	}
	freeAll(hash, M);
	return 0;
}