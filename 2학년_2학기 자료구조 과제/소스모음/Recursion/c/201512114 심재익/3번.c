#pragma warning (disable:4996)
#include <stdio.h>
#include<string.h>
#define MAX 100

int GetSum(int data[], int K, int start, int end,int count)
{
	int sum = data[start] + data[end];

	if (start >= end)
		return count;

	if (sum == K)
		GetSum(data, K, start + 1, end - 1, count + 1);
	else if (sum > K)
		GetSum(data, K, start, end - 1, count);
	else if (sum < K)
		GetSum(data, K, start + 1, end, count);
}

int main()
{
	int data[MAX];
	int N, K;
	printf("N값을 입력하세요 :");
	scanf(" %d", &N);
	int count = 0;

	int start = 0, end = N - 1;
	
	printf("숫자들을 입력하세요 : ");
	for (int i = 0; i < N; i++)
		scanf(" %d", data+i);

	printf("K의 값을 입력하세요 ; ");
	scanf(" %d", &K);

	int how_many = GetSum(data,K,start,end,count);
	
	printf("how_many = %d\n",how_many);
}
