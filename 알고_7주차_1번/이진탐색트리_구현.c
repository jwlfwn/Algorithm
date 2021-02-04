#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/* ��ó�� ��Ʈ�� ����Ű�� ����� �ּҰ��� �ٲ�� ��쿡�� ����������(�����͸� ����Ű�� ������)�����
   �Լ��� ȣ���ϸ鼭 ����Ҷ� �ּҸ� ����� �� ���� */
typedef struct node
{
	int key;
	struct node *parent;
	struct node *lChild;
	struct node *rChild;
}node;

node *getnode()
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->parent = NULL;
	newnode->lChild = NULL;
	newnode->rChild = NULL;
	return newnode;
}

int isExternal(node *v)
{
	if (v->lChild == NULL && v->rChild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(node *v)
{
	if (v->lChild != NULL || v->rChild != NULL)
		return 1;
	else  // �Ѵ�(&&) NULL�̸�
		return 0;
}

node *treeSearch(node *root, int k)
{
	if (isExternal(root))
		return root;

	if (root->key == k)
		return root;
	else if (k < root->key)
		return treeSearch(root->lChild, k);  // return
	else
		return treeSearch(root->rChild, k);  // return

}

int findElement(node *root, int k)
{
	node *w = treeSearch(root, k);

	if (isExternal(w))  // Ű�� �������� ������
		return 0;
	else  // Ű�� �����ϸ�
		return 1;
}

void expandExternal(node *w)
{
	w->lChild = getnode();
	w->rChild = getnode();
	w->lChild->parent = w;
	w->rChild->parent = w;
	return;
}

void insertItem(node *root, int k)
{
	node *w = treeSearch(root, k);
	//if (isInternal(w))
		//return;
	//else
	//{
		w->key = k;
		expandExternal(w);
		return;
	//}
}

void preorder_travel(node *root)  // ������ȸ
{
	if (isExternal(root))
		return;

	printf(" %d", root->key);
	if (isInternal(root->lChild))
		preorder_travel(root->lChild);
	if (isInternal(root->rChild))
		preorder_travel(root->rChild);
}

node *inOrderSucc(node *w)
{
	w = w->rChild;  // �ϴ� w�� ���γ���̹Ƿ� �������ڽ��� ����
	//if (isExternal(w))
		//return 0;
	while (isInternal(w->lChild))
		w = w->lChild;
	return w;
}

node *sibling(node *z)
{
	if (z == z->parent->lChild)
		return z->parent->rChild;
	else
		return z->parent->lChild;
}

void reduceExternal(node *z, node **q) // �ܺγ��� �� �ܺγ���� �θ��带 �Բ� �����ϴ� �Լ�, ������z�� �ܺγ�带 �޾ƾ��ԡ�
{ // q = &root
	node *w, *zs, *g;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL)  // ��Ʈ����̸�
	{
		*q = zs;  // ��Ʈ����� �ּҰ� �ٲ�Ƿ� �Լ����ڴ� ���������� *q=root
		zs->parent = NULL;
	}
	else
	{
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(z);
	free(w);
	/*
	node *zs = sibling(z);
	node *y = z->parent;
	node *py = y->parent;
	if (z->parent->parent == NULL)  // z�� �θ��尡 ��Ʈ����̸�
	{
		*q = zs;
		zs->parent = NULL; // ��
		free(y);
		free(z);
		return;
	}

	if (py->lChild == y)
	{
		py->lChild = zs;
		zs->parent = py;
	}
	else
	{
		py->rChild = zs;
		zs->parent = py;
	}
	free(y);
	free(z);
	return;
	*/
}

int removeElement(node **proot, int e)  // reduceExternal, inOrderSucc, sibling
{
	int save;
	node *w, *z, *y;
	w = treeSearch(*proot, e); // *proot = root = root�� ����Ű�� �ִ� ����� �ּ�
	if (isExternal(w))
		return 0;
	save = w->key;
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))  // case1 : w�� �ڽĳ���� �ϳ��� �ܺγ���� ���
		reduceExternal(z, proot);  // proot = &root = ������ ��Ʈ�� �ּ�
	else  // case2 : w�� �ڽĳ�尡 ��� ���γ���� ���
	{
		y = inOrderSucc(w);  // w�� ������ȸ ����� ã��
		z = y->lChild;
		w->key = y->key;
		reduceExternal(z, proot);
	}
	return save;

	/*
	node *w = treeSearch(*proot, e);
	int save;

	if (isExternal(w))  // �����ҳ�尡 ������
		return 0;
	else  // �����ҳ�尡 ������ case1, case2�� ����
	{
		save = w->key;
		if (isExternal(w->lChild) == 1 || isExternal(w->rChild) == 1)  // case1 : �ڽĳ���� �ܺγ�尡 �ϳ��� �������
		{
			if (isExternal(w->lChild))
				reduceExternal(w->lChild, proot);
			else
				reduceExternal(w->rChild, proot);
		}
		else  // case2 : �ڽĳ�尡 ��� ���γ���� ���
		{
			node *y = inOrderSucc(w);  // y�� w�� ������ȸ �����(w�� �������ڽ����� �ѹ����� ���γ�帶������ ���ö����� �������� �̵�)
			node *z = y->lChild;  // z�� y�� �ڿ����ڽġ��� �ܺγ��
			w->key = y->key;
			reduceExternal(z, proot);
		}
		return save;
	}
	*/
}

int main()
{
	int e;
	char str;
	node *root = getnode();

	while (1)
	{
		scanf("%c", &str);
		switch (str)
		{
		case 'i':
			scanf("%d", &e); getchar();
			insertItem(root, e);
			break;
		case 'd':
			scanf("%d", &e); getchar();
			if (removeElement(&root, e) == 0)
				printf("X\n");
			else
				printf("%d\n", e);
			break;
		case 's':
			scanf("%d", &e); getchar();
			if (findElement(root, e))
				printf("%d\n", e);
			else
				printf("X\n");
			break;
		case 'p':
			preorder_travel(root);
			printf("\n");
			break;
		case 'q':
			exit(-1);
			break;
		}
	}

	return 0;
}