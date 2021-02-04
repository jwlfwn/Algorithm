#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int n, max_idx, temp;
	int *arr;

	scanf("%d", &n);

	arr = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
		scanf("%d", arr+i);

	for (int i = n - 1; i > 0; i--)  
	{
		max_idx = i; 
		for (int j = 0; j < i; j++)
		{
			if (arr[j] >= arr[max_idx])
				max_idx = j;
		}

		temp = arr[i];
		arr[i] = arr[max_idx];
		arr[max_idx] = temp;
	}

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);

	return;
}