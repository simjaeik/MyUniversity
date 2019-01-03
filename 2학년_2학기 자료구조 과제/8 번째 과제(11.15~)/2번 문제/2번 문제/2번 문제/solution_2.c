#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solution_2.h"
#include "stackADT.h"

int list_num = 1;
void commender()
{
	char line[MAX_SIZE];
	char N[MAX_SIZE];

	printf("N의 값을 입력하세요 : ");
	fgets(N, MAX_SIZE, stdin);
	int num = atoi(N);

	for (int n = 0; n < num; n++) {
		Stack s = create();
		printf("라인을 입력하세요 : ");
		fgets(line, MAX_SIZE, stdin);
		for (int i = 0; i < strlen(line); i++)
		{
			handle_stack(s, line[i]);
		}
		printf("\n");
		destroy(s);
		list_num = 1;
	}
}

void handle_stack(Stack s, char input)
{
	if (input == '(' || input==')')
	{
		if (input == '(')
		{
			push(s, input);
			s->top->number = list_num++;
			printf("%d ", s->top->number);
		}
		else if (input == ')')
		{
			if (s->top == NULL);
			printf("%d ", pop(s));
		}
	}
}