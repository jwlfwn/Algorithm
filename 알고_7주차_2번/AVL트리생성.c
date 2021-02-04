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

int updateHeight(node *w)  // 높이갱신여부를 반환
{
	int h;
	h = maximum(w->lChild->height, w->rChild->height) + 1;
	if (h != w->height)  // 이부분 다시 확인
	{
		w->height = h;
		return 1;  // 갱신함
	}
	else
		return 0;  // 갱신안함
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
	node *a, *b, *c, *T0, *T1, *T2, *T3;  // 중위순회로 적용
	// step 1. 중위순회에 따라 a,b,c및 부트리 적용 (4가지 case가 있음) //
	if (z->key < y->key && y->key < x->key)  // 단일회전
	{
		a = z, b = y, c = x;
		T0 = a->lChild, T1 = b->lChild, T2 = c->lChild, T3 = c->rChild;
	}
	else if (z->key > y->key && y->key > x->key)  // 단일회전
	{
		a = x, b = y, c = z;
		T0 = a->lChild, T1 = a->rChild, T2 = b->rChild, T3 = c->rChild;
	}
	else if (y->key > x->key && x->key > z->key)  // 이중회전 RL
	{
		a = z, b = x, c = y;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}
	else  // 이중회전 LR
	{
		a = y, b = x, c = z;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}

	// step 2. z의 부모를 b와 연결시켜줌 //
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

	// step 3. b를 루트로 하는 부트리 제작 //
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

// 인자로 루트노드도 줄수있음->수정
void searchAndFixAfterInsertion(node **q, node *w)  // q = proot = &root
{
	node *z, *y, *x;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)  // w가 루트노드 일때
		return;
	z = w->parent;  // w에서 T의 루트로 향해 올라가면서 불균형노드 찾기
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;
	//균형이 안맞을 경우 -> 높은자식찾기 z-y-x //
	if (z->lChild->height > z->rChild->height)  // z의 높은자식은 y
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)  // y의 높은자식은 x
		x = y->lChild;
	else
		x = y->rChild;
	restructure(q, x, y, z);
	return;
}

void insertItem(node **proot, int k)  // proot = &root
{
	node *w = treeSearch(*proot, k);
	
	if (isInternal(w)) // 중복있는경우
		return;
	else
	{
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(proot, w);
		return;
	}
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