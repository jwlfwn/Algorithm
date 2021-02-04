#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key;
	int height;
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

int isExternal(node *w)
{
	if (w->lChild == NULL && w->rChild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(node *w)
{
	if (w->lChild != NULL && w->rChild != NULL)
		return 1;
	else
		return 0;
}

node *treeSearch(node *w, int k)
{
	if (isExternal(w))
		return w;

	if (w->key == k)
		return w;
	else if (k < w->key)
		return treeSearch(w->lChild, k);
	else
		return treeSearch(w->rChild, k);
}

int findElement(node *root, int k)
{
	node *w = treeSearch(root, k);
	if (isExternal(w))
		return 0;
	else
		return 1;
}

void preorder_travel(node *root)
{
	if (isExternal(root))
		return;
	printf(" %d", root->key);
	if (isInternal(root->lChild))
		preorder_travel(root->lChild);
	if (isInternal(root->rChild))
		preorder_travel(root->rChild);
}

void expandExternal(node *w)
{
	w->lChild = getnode();
	w->rChild = getnode();
	w->lChild->parent = w;
	w->rChild->parent = w;
	return;
}

int maximum(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

int updateHeight(node *w)  // ���̰��ſ��θ� ��ȯ
{
	int h;
	h = maximum(w->lChild->height, w->rChild->height) + 1;
	if (h != w->height)  // �̺κ� �ٽ� Ȯ��
	{
		w->height = h;
		return 1;  // ������
	}
	else
		return 0;  // ���ž���
}

int isBalanced(node *w)
{
	if (w->lChild->height >= w->rChild->height)
		return (w->lChild->height) - (w->rChild->height) < 2;
	else
		return (w->rChild->height) - (w->lChild->height) < 2;
}

node *restructure(node **pq, node *x, node *y, node *z)  // pq = q = proot = &root
{
	node *a, *b, *c, *T0, *T1, *T2, *T3;  // ������ȸ�� ����
	// step 1. ������ȸ�� ���� a,b,c�� ��Ʈ�� ���� (4���� case�� ����) //
	if (z->key < y->key && y->key < x->key)  // ����ȸ��
	{
		a = z, b = y, c = x;
		T0 = a->lChild, T1 = b->lChild, T2 = c->lChild, T3 = c->rChild;
	}
	else if (z->key > y->key && y->key > x->key)  // ����ȸ��
	{
		a = x, b = y, c = z;
		T0 = a->lChild, T1 = a->rChild, T2 = b->rChild, T3 = c->rChild;
	}
	else if (y->key > x->key && x->key > z->key)  // ����ȸ�� RL
	{
		a = z, b = x, c = y;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}
	else  // ����ȸ�� LR
	{
		a = y, b = x, c = z;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}

	// step 2. z�� �θ� b�� ��������� //
	if (z->parent == NULL)  // *pq = root, pq = &root
	{
		*pq = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)
	{
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else
	{
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	// step 3. b�� ��Ʈ�� �ϴ� ��Ʈ�� ���� //
	a->lChild = T0;
	T0->parent = a;
	a->rChild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	T2->parent = c;
	c->rChild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(node **q, node *w)  // q = proot = &root
{
	node *z, *y, *x;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)  // w�� ��Ʈ��� �϶�
		return;
	z = w->parent;  // w���� T�� ��Ʈ�� ���� �ö󰡸鼭 �ұ������ ã��
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))  // !updateHeight(z)
		return;
	//������ �ȸ��� ��� -> �����ڽ�ã�� z-y-x //
	if (z->lChild->height > z->rChild->height)  // z�� �����ڽ��� y
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)  // y�� �����ڽ��� x
		x = y->lChild;
	else
		x = y->rChild;
	restructure(q, x, y, z);
	return;
}

void insertItem(node **proot, int k)  // proot = &root
{
	node *w = treeSearch(*proot, k);

	if (isInternal(w)) // �ߺ��ִ°��
		return;
	else
	{
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(proot, w);
		return;
	}
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
void searchAndFixAfterRemoval(node **q, node *z)  // q = proot = &root
{
	node *y, *x, *b;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))  // !updateHeight(z)
		return;
	//������ �ȸ��� ��� -> �����ڽ�ã�� z-y-x //
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;


	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else  // y->lChild->height == y->rChild->height (�����϶����� ������)
	{
		if (z->lChild == y)
			x = y->lChild;
		else
			x = y->rChild;
	} 
	b = restructure(q, x, y, z);
	if (b->parent == NULL)
		return;
	searchAndFixAfterRemoval(q, b->parent);
}

node *reduceExternal(node *z, node **q)  // q = proot = &root
{
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
	return zs;
}

int removeElement(node **proot, int k)  // proot = &root
{
	int save;
	node *w, *z, *y, *zs;
	w = treeSearch(*proot, k); // *proot = root = root�� ����Ű�� �ִ� ����� �ּ�
	if (isExternal(w))
		return 0;
	save = w->key;
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))  // case1 : w�� �ڽĳ���� �ϳ��� �ܺγ���� ���
		zs = reduceExternal(z, proot);  // proot = &root = ������ ��Ʈ�� �ּ�
	else  // case2 : w�� �ڽĳ�尡 ��� ���γ���� ���
	{
		y = inOrderSucc(w);  // w�� ������ȸ ����� ã��
		z = y->lChild;
		w->key = y->key;
		zs = reduceExternal(z, proot);
	}
	searchAndFixAfterRemoval(proot, zs->parent);
	return save;
}

void main()
{
	int key;
	char str;
	node *root = getnode();

	while (1)
	{
		scanf("%c", &str);
		switch (str)
		{
		case 'i':
			scanf("%d", &key); getchar();
			insertItem(&root, key);
			break;
		case 'd':
			scanf("%d", &key); getchar();
			if (removeElement(&root, key) == 0)
				printf("X\n");
			else
				printf("%d\n", key);
			break;
		case 's':
			scanf("%d", &key); getchar();
			if (findElement(root, key))
				printf("%d\n", key);
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

	return;
}
