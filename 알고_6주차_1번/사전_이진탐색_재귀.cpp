#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int search(int *, int, int, int);

int main()
{
	int n, key, *arr, p;

	scanf("%d %d", &n, &key);

	arr = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);

	p = search(arr, 0, n - 1, key);

	printf(" %d", p);

	return 0;
}

int search(int *arr, int l, int r, int key)
{
	int mid = (l + r) / 2;

	if (arr[l] > key)
		return -1;
	if (l == r)
		return l;

	if (key == arr[mid])
		return mid;
	else if (key < arr[mid])
	{
		if (key >= arr[mid - 1])
			return mid - 1;
		search(arr, l, mid - 1, key);
	}
	else
	{
		if (key < arr[mid + 1])
			return mid;
		search(arr, mid + 1, r, key);
	}
}