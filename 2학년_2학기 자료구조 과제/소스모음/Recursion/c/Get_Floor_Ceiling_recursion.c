#pragma warning (disable:4996)
#include <stdio.h>
#define MAX 100

int GetFloor(int data[], int K, int start, int end)
{
	int mid = (start + end) / 2;
	if (data[end] < K)return data[end];
	else if (data[start] > K)return -1;

	if (end-start == 1 && data[mid] < K)return data[mid];

	if (start == end) {
		if (data[mid] == K) 
			return data[mid];
		else return -1;						//can't found
	}
	else if (data[mid] > K) GetFloor(data, K, start, mid - 1);
	else if (data[mid] < K)GetFloor(data, K, mid, end);
	else return data[mid];
}

int GetCeiling(int data[], int K, int start, int end)
{
	int mid = (start + end) / 2;
	if (data[end] < K)return -1;
	else if (data[start] > K)return data[start];

	if (end-start== 0 && data[mid+1] > K)return data[mid+1];

	if (start == end) {
		if (data[mid] == K)
			return data[mid];
		else return -1;
	}
	if (data[mid] > K) GetCeiling(data, K, start, mid);
	else if (data[mid] < K) GetCeiling(data, K,mid+1, end);
	else return data[mid];
}

int main()
{
	int data[MAX];
	int N, K;
	printf("N값을 입력하세요 :");
	scanf(" %d", &N);
	int result = 0;

	int start = 0, end = N - 1;

	printf("숫자들을 입력하세요 : ");
	for (int i = 0; i < N; i++)
		scanf(" %d", data + i);
	data[N] = '\0';

	printf("K의 값을 입력하세요 ; ");
	scanf(" %d", &K);

	int floor = GetFloor(data, K, 0, N - 1);
	int ceiling = GetCeiling(data, K, 0, N - 1);

	printf("GetFloort = %d\n", floor);
	printf("GetCeiling = %d\n", ceiling);
}
