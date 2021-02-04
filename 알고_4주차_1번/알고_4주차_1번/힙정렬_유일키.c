#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int H[100], n, cnt = 0; // cnt�� ���Խ��϶��� �ʿ�

//void rBuildHeap(int i);
//void buildHeap();
void insertItem(int key);
void upHeap(int i);
void downHeap(int i);
void swapElements(int parent, int child);
void inPlaceHeapSort();
void printArray();

void main()
{
	int n_copy, key;

	scanf("%d", &n);
	n_copy = n;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &key);
		insertItem(key);  // �ִ���-������-���Խ�-1��
	}

	//rBuildHeap(1);  // �ִ���-������-�����-���-1��
	//buildHeap();  // �ִ���-������-�����-�����-1��
	inPlaceHeapSort();  // ������-2��
	n = n_copy;
	printArray();

	return;
}
/*
void rBuildHeap(int i)
{
	if (i > n)
		return;

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}
*/
/*
void buildHeap()
{
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
	return;
}
*/

void insertItem(int key)
{
	cnt++;
	H[cnt] = key;
	upHeap(cnt);
	return;
}

void upHeap(int i)
{
	if (i == 1)
		return;
	if (H[i] <= H[i / 2])
		return;
	//if(H[i] > H[i/2] : ����Ű
	swapElements(i / 2, i);
	upHeap(i / 2);
}

void downHeap(int i)
{
	int bigger, l, r;  // bigger�� �ε������� (����)

	l = 2 * i;
	r = 2 * i + 1;

	if (l > n)  // �ڽĳ�尡������
		return;

	// if(l <= n)
	bigger = l;
	if (r <= n)  // �����ʿ��� �ڽ��� ������
		if (H[bigger] < H[r])  // ����Ű
			bigger = r;

	if (H[bigger] <= H[i])
		return;

	// if(H[bigger] > H[i]) �϶� �����ϹǷ� ����Ű
	swapElements(i, bigger);
	downHeap(bigger);
}

void swapElements(int parent, int child)
{
	int temp;
	temp = H[parent];
	H[parent] = H[child];
	H[child] = temp;
	return;
}

void inPlaceHeapSort()
{
	int temp;

	while (n >= 2)
	{
		temp = H[n];
		H[n] = H[1];
		H[1] = temp;
		n--;
		downHeap(1);
	}
	return;
}

void printArray()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	return;
}