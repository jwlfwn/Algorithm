#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int n;

typedef struct node
{
	struct node *next;
	int elem;
}node;

node *last = NULL;

void make_node(node *L, int e);
node *mergeSort(node *L);
node *merge(node *L1, node *L2);
node *mg_partition(node *L, int k);

node *getnode(int e)
{
	node *newnode = (node *)malloc(sizeof(node));
	newnode->next = NULL;
	newnode->elem = e;
	return newnode;
}

void main()
{
	int e;
	node *L = (node *)malloc(sizeof(node));  // ���Լ����ڷ� �����ϱ����ؼ� ��带 �Ҵ�����ߵʡ�
	L->next = NULL;
	L->elem = '\0';

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &e);
		make_node(L, e);	
	}

	L = mergeSort(L);

	while(L!=NULL)
	{
		printf(" %d", L->elem);
		L = L->next;
	}

	return;
}

void make_node(node *L, int e)
{
	if (L->elem == '\0')
	{
		L->elem = e;
		last = L;
	}
	else
	{
		last->next = getnode(e);
		last = last->next;
	}
	return;
}

node *mergeSort(node *L)
{
	node *Rnode = NULL;

	if (L->next != NULL)
	{
		n /= 2;
		Rnode = mg_partition(L, n);
		L = mergeSort(L);
		Rnode = mergeSort(Rnode);
		L = merge(L, Rnode);
	}
	return L;
}

node *mg_partition(node *L, int k)
{
	node *cur = L;
	node *Rnode = NULL;

	for (int i = 0; i < k-1; i++)
	{
		cur = cur->next;
	}
	Rnode = cur->next;
	cur->next = NULL;
	return Rnode;
}

node *merge(node *L1, node *L2)  // O(1)�� ������ ��밡����. ���ο� ���Ḯ��Ʈ�� �����ϸ� �ȵ� -> O(n)�̹Ƿ�
{
	node *merge, *cur = NULL;

	if (L1->elem <= L2->elem)
		merge = L1;
	else
		merge = L2;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->elem <= L2->elem)
		{
			cur = L1;
			if (cur->next == NULL)
			{
				L1 = L1->next;
				break;
			}
			else
			{
				L1 = L1->next;
			}

			if (L1->elem > L2->elem)  // �ڵ�ȣ����ߵʡڸſ��߿�� n=9�̰� 8 1 1 1 1 2 4 1 1 �Է�������
			{
				cur->next = L2;
			}
		}
		else
		{
			cur = L2;
			if (cur->next == NULL)
			{
				L2 = L2->next;
				break;
			}
			else
			{
				L2 = L2->next;
			}

			if (L1->elem <= L2->elem)
			{
				cur->next = L1;
			}
		}
	}

	if (L1 == NULL)
		cur->next = L2;
	else
		cur->next = L1;

	return merge;
}