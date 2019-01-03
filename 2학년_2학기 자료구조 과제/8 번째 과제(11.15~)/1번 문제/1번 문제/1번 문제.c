#pragma warning (disable:4996)
#include <stdio.h>
#include "stackADT.h"
#include "solution_1.h"
#include <time.h>

int main()
{
	clock_t start, end;

	start = clock();

	Stack s1 = create();
	FILE *fp = fopen("input.txt", "r");
	
	int T = 0;
	fscanf(fp, " %d", &T);

	commender(fp,T,s1);
	
	fclose(fp);
	end = clock();

	printf("걸린 시간 : %.3lf초\n", (end-start)/(double)1000);
	return;
}