#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int H[100], n = 0;

void insertItem(int key);
void upHeap(int i);
void swapElements(int parent,int child);
int removeMax();
void downHeap(int i);
void printHeap();

void main()
{
	int key;
	char str;

	while (n < 100)
	{
		scanf("%c", &str);

		switch (str)
		{
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			break;
		case 'd':
			if (n < 1)
				continue;
			printf("%d\n", removeMax());
			break;
		case 'p':
			if (n < 1)
				continue;
			printHeap();
			break;
		case 'q':
			exit(-1);
			break;
		}
	}
	return;
}

void insertItem(int key)
{
	n = n + 1;
	H[n] = key;
	upHeap(n);
	return;
}

void upHeap(int i)
{
	if (i == 1)
		return;
	if (H[i / 2] > H[i])
		return;
	swapElements(i / 2, i);
	upHeap(i / 2);
}

void swapElements(int parent,int child)
{
	int temp;
	temp = H[parent];
	H[parent] = H[child];
	H[child] = temp;
}

int removeMax()
{
	int key = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	return key;
}

void downHeap(int i)
{
	int bigger, l, r;
	
	l = 2 * i;
	r = 2 * i + 1;
	if (l > n)  // 외부노드 판별  
		return;
	bigger = l;
	if (r <= n)  // 만약 r>n이면 r이 존재하지 않다는 뜻
		if (H[bigger] < H[r])
			bigger = r;
	if (H[i] > H[bigger])  // 부모가 자식보다 크면 리턴
		return;
	swapElements(i, bigger);
	downHeap(bigger);
}

void printHeap()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
	return;
}