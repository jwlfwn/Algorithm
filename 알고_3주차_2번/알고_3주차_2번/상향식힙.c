#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int H[100], n;

//void rBuildHeap(int i);
void buildHeap();
void swapElements(int parent, int child);
void downHeap(int i);
void printHeap();

void main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	//rBuildHeap(1);
	buildHeap();
	printHeap();
	return;
}

/* ��� �����
void rBuildHeap(int i)
{
	if (i > n)
		return;

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
	<�м�>
	�ð����⵵�� ����ϱ� ���� ���̿� ���� ��尳���� downheap�� �ݺ�Ƚ���� �˾ƾ��Ѵ�.
	���̰� 0�϶� ��尳���� n/2^1, ���̰� 1�϶� ��尳���� n/2^2�̴�. (������������ ���� ���� �Ҽ�ù°�ڸ����� �ø����Ѵ�.)
	�׸��� ���̰� 0�϶� downHeap �ݺ��� 0��, 1�϶� 1��, 2�϶� 2�� �̴�.
	�̷��� ��Ģ���� ������ ���� rBuildHeap�� downHeap�� ���ڷ� i=n����1���� �����ϹǷ� �̸� ������ ǥ���ϸ�,
	(n/2^1*0)+(n/2^2*1)+(n/2^3*2)+...+(n/2^(h+1)*h) = n*(0+1/4+2/8+...+h/2^(h+1)) �̴�.
	���� �ð����⵵�� O(n)�̴�.

	return;
}*/

/* ����� ����� */
void buildHeap()
{
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
	/* <�м�>
	���� ���̿� ���� ��尳���� downheap�� �ݺ�Ƚ���� ��Ģ���� ������ buildHeap�� for���� ����
	downHeap�� ���ڷ� i=n/2���� 1���� �����ϹǷ� �̸� ������ ǥ���ϸ�,
	{(n/2)/2^2*1}+{(n/2)/2^3*2}+{(n/2)/2^4*3}+...+{(n/2)/2^(h+1)*h} = (n/2)*(1/4+2/8+3/16+...+h/2^(h+1)) �̴�.
	���� �ð����⵵�� O(n)�̴�.
	��������� ��ͻ�����̳� ����ͻ���� ��� ������ O(n)�� �ð����⵵�� ������.
	*/
	return;
}

void swapElements(int parent, int child)
{
	int temp;
	temp = H[parent];
	H[parent] = H[child];
	H[child] = temp;
	return;
}

void downHeap(int i)
{
	int bigger, l, r;

	l = 2 * i;
	r = 2 * i + 1;
	if (l > n)
		return;
	bigger = l;
	if (r <= n)
		if (H[bigger] < H[r])
			bigger = r;
	if (H[i] > H[bigger])
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