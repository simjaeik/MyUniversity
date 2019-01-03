#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define MAX_SIZE 100000
int data_list[MAX_SIZE];
int smallest_in_group[MAX_SIZE];
int cnt = 0;

void handle_data_list(FILE *fp, int N, int root_N);
void find_smallest_list(FILE *fp, int i, int num);
int find_smalldata(int n, int m,int N);

int main()
{
	int N = 0, i = 0, j = 0;
	FILE *fp = fopen("data.txt", "r");
	fscanf(fp, "%d ", &N);
	int root_N = sqrt(N);

	handle_data_list(fp, N, root_N);

	while (1) {
		printf("Selcet i / j : ");
		scanf("%d %d", &i, &j);
		if (i == -1 || j == -1)
			break;

		int smallest_number = find_smalldata(i, j, root_N);

		printf("Smallest Number = %d\n", smallest_number);
	}
}

int find_smalldata(int n, int m,int N) {
	int small_n = data_list[n];
	for (int i = n+1; i < ((n / N) + 1) * 100; i++) {
		if (small_n > data_list[n])
			small_n = data_list[n];
	}
	int small_m = data_list[m];
	for (int i = (m / N) * 100; i < m; i++) {
		if (small_m > data_list[m])
			small_m = data_list[m];
	}

	n /= N, m /= N;
	int smallest_number = (small_n < small_m ? small_n : small_m);

	for (int i = n+1; i < m; i++) {
		if (smallest_number > smallest_in_group[i])
			smallest_number = smallest_in_group[i];
	}
	return smallest_number;
}

void handle_data_list(FILE *fp, int N,int root_N) {
	for (int i = 0; i < N / root_N; i++) {
		find_smallest_list(fp, i, root_N);
	}
}

void find_smallest_list(FILE *fp,int i,int num) {
	int number = 0;
	fscanf(fp, "%d ", &number);
	data_list[cnt++] = number;

	smallest_in_group[i] = number;
	for (int n = 0; n < num - 1; n++) {
		if (fscanf(fp, "%d ", &number) == EOF)
			return;
		data_list[cnt++] = number;

		if (smallest_in_group[i] > number) {
			smallest_in_group[i] = number;
		}
	}
}