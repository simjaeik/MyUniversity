#pragma warning (disable:4996)
#include <stdio.h>
#include "solution_1.h"
#include "stackADT.h"

void commender(FILE *fp, int T, Stack s);
int get_h(Stack s, int read_num);

void commender(FILE *fp, int T, Stack s)
{
	int read_num = 0, sum_hx = 0;
	for (int i = 0; i < T; i++)
	{
		int N=0; int hx = 0;
		
		fscanf(fp, " %d", &N);

		fscanf(fp, " %d", &read_num);
		push(s, read_num);
		for (int n = 1; n < N; n++)
		{
			fscanf(fp," %d", &read_num);

			if ((hx=get_h(s, read_num)) != 0) {
				sum_hx = (sum_hx + hx) % 1000000;
			}
		}
		printf("h(%d) : %d \n", i, sum_hx);
		make_empty(s);
		sum_hx = 0;
	}
}

int get_h(Stack s, int read_num)
{
	int size = 0;

	if (read_num < s->top->data)
	{
		push(s, read_num);
		return 0;
	}
	else if (read_num >= s->top->data)
	{
		size = s->top->size + 1;
		pop(s);
		while (s->top != NULL && read_num >= s->top->data)
		{
			size += s->top->size + 1;
			pop(s);
		}
		push(s, read_num);
		s->top->size = size;
		return size;
	}
}