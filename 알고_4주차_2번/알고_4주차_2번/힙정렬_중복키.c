#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int H[100], n;

void rBuildHeap(int i);
void downHeap(int i);
void swapElements(int parent, int child);
void inPlaceHeapSort();
void printArray();

void main()
{
	int n_copy;

	scanf("%d", &n);
	n_copy = n;

	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	rBuildHeap(1);  // 최대힙-순차힙-상향식-재귀-1기
	inPlaceHeapSort();  // 순차힙-2기
	n = n_copy;
	printArray();

	return;
}

void rBuildHeap(int i)
{
	if (i > n)
		return;

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}

void downHeap(int i)
{
	int bigger, l, r;  // bigger은 인덱스값임 (주의)

	l = 2 * i;
	r = 2 * i + 1;

	if (l > n)  // 자식노드가없으면
		return;

	// if(l <= n)
	bigger = l;
	if (r <= n)  // 오른쪽에도 자식이 있으면
		if (H[bigger] <= H[r])  // 중복키
			bigger = r;

	if (H[bigger] < H[i])
		return;

	// if(H[bigger] >= H[i]) 일때 수행하므로 중복키
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
}

void printArray()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	return;
}