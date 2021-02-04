#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
/* 맨처음 루트가 가리키는 노드의 주소값이 바뀌는 경우에는 이중포인터(포인터를 가리키는 포인터)를써야
   함수를 호출하면서 사용할때 주소를 기억할 수 있음 */
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
	else  // 둘다(&&) NULL이면
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

	if (isExternal(w))  // 키가 존재하지 않으면
		return 0;
	else  // 키가 존재하면
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

void preorder_travel(node *root)  // 전위순회
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
	w = w->rChild;  // 일단 w는 내부노드이므로 오른쪽자식이 있음
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

void reduceExternal(node *z, node **q) // 외부노드와 그 외부노드의 부모노드를 함께 삭제하는 함수, ★인자z는 외부노드를 받아야함★
{ // q = &root
	node *w, *zs, *g;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL)  // 루트노드이면
	{
		*q = zs;  // 루트노드의 주소가 바뀌므로 함수인자는 이중포인터 *q=root
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
	if (z->parent->parent == NULL)  // z의 부모노드가 루트노드이면
	{
		*q = zs;
		zs->parent = NULL; // ★
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
	w = treeSearch(*proot, e); // *proot = root = root가 가리키고 있는 노드의 주소
	if (isExternal(w))
		return 0;
	save = w->key;
	z = w->lChild;
	if (!isExternal(z))
		z = w->rChild;
	if (isExternal(z))  // case1 : w의 자식노드중 하나라도 외부노드일 경우
		reduceExternal(z, proot);  // proot = &root = 포인터 루트의 주소
	else  // case2 : w의 자식노드가 모두 내부노드일 경우
	{
		y = inOrderSucc(w);  // w의 중위순회 계승자 찾기
		z = y->lChild;
		w->key = y->key;
		reduceExternal(z, proot);
	}
	return save;

	/*
	node *w = treeSearch(*proot, e);
	int save;

	if (isExternal(w))  // 삭제할노드가 없으면
		return 0;
	else  // 삭제할노드가 있으면 case1, case2가 있음
	{
		save = w->key;
		if (isExternal(w->lChild) == 1 || isExternal(w->rChild) == 1)  // case1 : 자식노드중 외부노드가 하나라도 있을경우
		{
			if (isExternal(w->lChild))
				reduceExternal(w->lChild, proot);
			else
				reduceExternal(w->rChild, proot);
		}
		else  // case2 : 자식노드가 모두 내부노드일 경우
		{
			node *y = inOrderSucc(w);  // y는 w의 중위순회 계승자(w의 오른쪽자식으로 한번가고 내부노드마지막이 나올때까지 왼쪽으로 이동)
			node *z = y->lChild;  // z는 y의 ★왼쪽자식★인 외부노드
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