#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _node
{
	struct _node *left;
	int node_num;
	struct _node *right;
}node;

void Init(node *root);
void make_tree(node *root, int x, int y, int z);
node *find(node *copy, char str);

void main()
{
	int n, s;
	int x, y, z;
	int len;
	char str[100];

	node *root = (node *)malloc(sizeof(node));
	node *copy = NULL;

	Init(root);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &x, &y, &z);
		make_tree(root, x, y, z);
	}

	scanf("%d", &s);
	for (int i = 0; i < s; i++)
	{
		copy = root;
		getchar();
		scanf("%s", str);
		len = strlen(str);
		printf(" %d", copy->node_num);
		for (int j = 0; j < len; j++)
		{
			copy = find(copy, str[j]);
			printf(" %d", copy->node_num);
		}
		printf("\n");
	}
}

void Init(node *root)
{
	root->left = NULL;
	root->right = NULL;
	root->node_num = 0;
}

void make_tree(node *root, int x, int y, int z)
{
	if (root->node_num == 0)
	{
		root->node_num = x;
		node *left = (node *)malloc(sizeof(node));
		node *right = (node *)malloc(sizeof(node));
		Init(left); Init(right);
		left->node_num = y;
		right->node_num = z;
		root->left = left;
		root->right = right;

		if (y == 0)
		{
			root->left = NULL;
			free(left);
		}
		if (z == 0)
		{
			root->right = NULL;
			free(right);
		}
	}
	else if (root->node_num == x && y != 0 && z != 0)
	{
		node *left = (node *)malloc(sizeof(node));
		node *right = (node *)malloc(sizeof(node));
		Init(left); Init(right);
		left->node_num = y;
		right->node_num = z;
		root->left = left;
		root->right = right;
	}
	else if (root->node_num == x && y != 0 && z == 0)
	{
		node *left = (node *)malloc(sizeof(node));
		Init(left);
		left->node_num = y;
		root->left = left;
	}
	else if (root->node_num == x && y == 0 && z != 0)
	{
		node *right = (node *)malloc(sizeof(node));
		Init(right);
		right->node_num = z;
		root->right = right;
	}
	else
	{
		if (root->left != NULL)
			make_tree(root->left, x, y, z);
		if (root->right != NULL)
			make_tree(root->right, x, y, z);
	}
}

node *find(node *copy, char str)
{
	if (str == 'R')
		return copy->right;
	else
		return copy->left;
}