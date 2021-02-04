#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void inPlaceSelectionSort(int n, int *arr);
void inPlaceInsertionSort(int n, int *arr);
void outPlaceSelectionSort(int n, int *arr);

void main()
{
	int n;
	int *A, *B;
	LARGE_INTEGER ticksPerSec1, ticksPerSec2;
	LARGE_INTEGER start1, end1, diff1, start2, end2, diff2;

	scanf("%d", &n);

	A = (int*)malloc(sizeof(int)*n);
	B = (int*)malloc(sizeof(int)*n);

	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		A[i] = B[i] = rand();
	}

	outPlaceSelectionSort(n, A);
	outPlaceSelectionSort(n, B);

	QueryPerformanceFrequency(&ticksPerSec1);
	QueryPerformanceCounter(&start1);
	inPlaceSelectionSort(n, A);
	QueryPerformanceCounter(&end1);

	QueryPerformanceFrequency(&ticksPerSec2);
	QueryPerformanceCounter(&start2);
	inPlaceInsertionSort(n, B);
	QueryPerformanceCounter(&end2);

	diff1.QuadPart = end1.QuadPart - start1.QuadPart;
	diff2.QuadPart = end2.QuadPart - start2.QuadPart;

	printf("%.9fms\n%.9fms", ((double)diff1.QuadPart / (double)ticksPerSec1.QuadPart)*1000, ((double)diff2.QuadPart / (double)ticksPerSec2.QuadPart) * 1000);

	return;
}

void outPlaceSelectionSort(int n, int *arr)
{
	int max_idx, temp;

	for (int i = n - 1; i > 0; i--)
	{
		max_idx = i;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] < arr[max_idx])
				max_idx = j;
		}

		temp = arr[i];
		arr[i] = arr[max_idx];
		arr[max_idx] = temp;
	}
}

void inPlaceSelectionSort(int n, int *arr)
{
	int max_idx, temp;

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
}

void inPlaceInsertionSort(int n, int *arr)
{
	int min, temp;

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
}