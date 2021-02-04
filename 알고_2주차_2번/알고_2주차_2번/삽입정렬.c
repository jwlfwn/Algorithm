#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int n, min, temp;
	int *arr;

	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);

	for (int i = 1; i < n; i++) 
	{
		temp = i;
		min = arr[temp];
		for (int j = i; j > 0; j--)
		{
			if (arr[j - 1] >= min)
			{
				arr[j] = arr[j - 1];
				temp = j - 1;
			}
		}
		arr[temp] = min;
	}

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);

	return;
}