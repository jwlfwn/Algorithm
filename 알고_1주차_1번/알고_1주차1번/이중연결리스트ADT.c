#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node *prev;
	char elem;
	struct node *next;
}node;

typedef struct list {
	node *H;
	node *T;
	int cnt;
}list;

void Init(list *plist);
void add(list *plist, int r, char e);
void delete(list *plist, int r);
char get(list *plist, int r);
void print(list *plist);

void main()
{
	int n, r;  // n : 연산갯수 r : 순위
	char s, e;  // e : 원소
	list list;

	Init(&list);

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
	{
		getchar();
		scanf("%c", &s);

		switch (s)
		{
		case 'A':
			getchar();
			scanf("%d", &r);
			getchar();
			scanf("%c", &e);
			if (r < 1 || r > list.cnt + 1)
			{
				printf("invalid position\n");
				continue;
			}
			add(&list, r, e);
			break;
		case 'D':
			getchar();
			scanf("%d", &r);
			if (r < 1 || r > list.cnt)
			{
				printf("invalid position\n");
				continue;
			}
			delete(&list, r);
			break;
		case 'G':
			getchar();
			scanf("%d", &r);
			if (r < 1 || r > list.cnt)
			{
				printf("invalid position\n");
				continue;
			}
			printf("%c\n", get(&list, r));
			break;
		case 'P':
			if (list.cnt == 0)
			{
				printf("invalid position\n");
				continue;
			}
			print(&list);
			break;
		}
	}

	return;
}

void Init(list *plist)
{
	plist->H = (node *)malloc(sizeof(node));
	plist->T = (node *)malloc(sizeof(node));

	plist->H->prev = NULL;
	plist->H->next = plist->T;

	plist->T->next = NULL;
	plist->T->prev = plist->H;

	plist->cnt = 0;
}

void add(list *plist, int r, char e)
{
	node *cur = plist->H;
	node *newnode = (node *)malloc(sizeof(node));
	newnode->elem = e;

	while (r > 1)
	{
		cur = cur->next;
		r--;
	}
	
	newnode->next = cur->next;
	cur->next = newnode;
	newnode->prev = cur;
	newnode->next->prev = newnode;

	plist->cnt++;
}

void delete(list *plist, int r)
{
	node *cur = plist->H;

	for (int i = 0; i < r; i++)
	{
		cur = cur->next;
	}

	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	plist->cnt--;
	free(cur);
}

char get(list *plist, int r)
{
	node *cur = plist->H;

	for (int i = 0; i < r; i++)
	{
		cur = cur->next;
	}

	return cur->elem;
}

void print(list *plist)
{
	node *cur = plist->H->next;

	for (int i = 0; i < plist->cnt; i++)
	{
		printf("%c", cur->elem);
		cur = cur->next;
	}

	printf("\n");
}
