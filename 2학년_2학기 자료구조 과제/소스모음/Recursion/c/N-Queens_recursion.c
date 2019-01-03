#pragma warning (disable:4996)
#include <stdio.h>
#include <cstdbool>
#include <stdlib.h>
#include <math.h>

int *queen;

bool promising(int level)
{
	for (int i = 1; i < level; i++) {
		if (queen[i] == queen[level])
			return false;
		else if (level -i == abs(queen[level] - queen[i]))
			return false;
	}
	return true;
}

int Queens(int N,int level){
	int sum = 0;
	if (!promising(level))
		return 0;
	else if (level == N)
		return 1;
	for (int i = 1; i <= N; i++) {
		queen[level+1] = i;
		sum +=Queens(N, level + 1);
	}
	return sum;
}

int main() {
	for (int N = 1; N <= 15; N++) {
		queen = (int *)malloc(sizeof(int)*(N+2));
		printf("N(%d) : %d \n", N, Queens(N, 0));
	}
	return 0;
}