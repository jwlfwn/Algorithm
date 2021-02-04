#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void inPlaceQuickSort(int *, int, int);
int *inPlacePartition(int *, int, int, int);
int find_pivot_index(int *, int, int);
void swap(int *, int, int);

int main()
{
	int n, *arr;

	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);  // &arr[i]

	inPlaceQuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);

	return 0;
}

void inPlaceQuickSort(int *arr, int l, int r)
{
	int k, *P;

	if (l >= r)  // �����Ǹ�
		return;
	k = find_pivot_index(arr, l, r);  // ������ �� �߾Ӱ����� �ǹ�(�ε�����)�� ����
	P = inPlacePartition(arr, l, r, k);
	inPlaceQuickSort(arr, l, P[0] - 1);
	inPlaceQuickSort(arr, P[1] + 1, r);
}

int *inPlacePartition(int *arr, int l, int r, int k)
{
	int i = l, j = r - 1;
	int *P = (int*)malloc(sizeof(int) * 2);
	int p = arr[k];  // p�� �ǹ���, k�� �ǹ��ε���
	swap(arr, k, r);

	while (i <= j)  // �������� ��������
	{
		while (i <= j && arr[i] < p)  // ����X + �ǹ����� ������
			i++;
		while (j >= i && arr[j] >= p)  // ����X + �ǹ����� ũ�ų�������
			j--;
		if (i < j)  // i=j �̸� �ٲ��ʿ䰡 ����
			swap(arr, i, j);
	}

	//�ߺ��� ���� ����� ������//
	P[0] = i;
	j = r - 1;
	while (i <= j)
	{
		while (i <= j && arr[i] == p)
			i++;
		while (j >= i && arr[j] > p)
			j--;
		if (i < j)
			swap(arr, i, j);
	}
	swap(arr, i, r);
	P[1] = i;

	return P;
}

int find_pivot_index(int *arr, int l, int r)
{
	int Pa, Pb, Pc;
	srand((unsigned int)time(NULL));
	Pa = rand() % (r - l + 1) + l;
	Pb = rand() % (r - l + 1) + l;
	Pc = rand() % (r - l + 1) + l;

	if (arr[Pa] >= arr[Pb])
	{
		if (arr[Pb] >= arr[Pc])
			return Pb;
		else if (arr[Pa] <= arr[Pc])
			return Pa;
		else
			return Pc;
	}
	else if (arr[Pa] >= arr[Pc])
		return Pa;
	else if (arr[Pb] >= arr[Pc])
		return Pc;
	else
		return Pb;
}

void swap(int *arr, int l, int r)
{
	int temp = arr[l];
	arr[l] = arr[r];
	arr[r] = temp;
}