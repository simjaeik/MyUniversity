#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATA_SIZE 100

void find_num();
void get_sum();

char data[DATA_SIZE];
int *num[DATA_SIZE];
int numbers[DATA_SIZE];
char *ptr = data;
int cnt = 0, sum = 0;

int main()
{
	fgets(data, DATA_SIZE, stdin);
	data[strlen(data) - 1] = '\0';
	
	find_num();
	get_sum();

	return 0;
}

void find_num()
{
	int i = 0;
	while (data[i] != '\0')
	{
		if (!isdigit(*(ptr + i))) {
			i++;
			continue;
		}
		int read_num = atoi(ptr + i);
		num[cnt++] = read_num;
		sum += read_num;
		while (read_num != 0){
			read_num /= 10;
			i++;
		}
	}
	data[strlen(data)] = '\0';
}

void get_sum()
{
	for (int i = 0; i < cnt; i++)
	{
		printf("%d", num[i]);
		if (i != cnt - 1)
			printf(" + ");
	}
	printf(" = %d\n", sum);
}