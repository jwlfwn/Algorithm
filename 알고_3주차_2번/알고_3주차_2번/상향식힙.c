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

/* 재귀 상향식
void rBuildHeap(int i)
{
	if (i > n)
		return;

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
	<분석>
	시간복잡도를 계산하기 위해 높이에 따른 노드개수와 downheap의 반복횟수를 알아야한다.
	높이가 0일때 노드개수는 n/2^1, 높이가 1일때 노드개수는 n/2^2이다. (나눠떨어지지 않은 수는 소수첫째자리에서 올림을한다.)
	그리고 높이가 0일때 downHeap 반복은 0번, 1일땐 1번, 2일땐 2번 이다.
	이러한 규칙성을 가지고 위의 rBuildHeap은 downHeap의 인자로 i=n부터1까지 대입하므로 이를 식으로 표현하면,
	(n/2^1*0)+(n/2^2*1)+(n/2^3*2)+...+(n/2^(h+1)*h) = n*(0+1/4+2/8+...+h/2^(h+1)) 이다.
	따라서 시간복잡도는 O(n)이다.

	return;
}*/

/* 비재귀 상향식 */
void buildHeap()
{
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
	/* <분석>
	위의 높이에 따른 노드개수와 downheap의 반복횟수의 규칙성을 가지고 buildHeap의 for문을 보면
	downHeap의 인자로 i=n/2부터 1까지 대입하므로 이를 식으로 표현하면,
	{(n/2)/2^2*1}+{(n/2)/2^3*2}+{(n/2)/2^4*3}+...+{(n/2)/2^(h+1)*h} = (n/2)*(1/4+2/8+3/16+...+h/2^(h+1)) 이다.
	따라서 시간복잡도는 O(n)이다.
	결론적으로 재귀상향식이나 비재귀상향식 모두 동일한 O(n)의 시간복잡도를 가진다.
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