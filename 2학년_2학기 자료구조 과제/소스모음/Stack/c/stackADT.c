# include <stdio.h>
# include <stdlib.h>
# include "stackADT.h"

# define MAX_CAPACITY 100
typedef int Item;

struct stack {
	Item *contents;
	int top;
	int size;
};

typedef struct stack *Stack;

static void terminate(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

Stack create()
{
	Stack s = (Stack)malloc(sizeof(struct stack));
	if (s == NULL)
		terminate("Error in create: stack could not be created.");
	s->contents = (Item *)malloc(MAX_CAPACITY * sizeof(Item));
	if (s->contents == NULL)
	{
		free(s);
		terminate("stack이 create 될 수 없습니다.");
	}
	s->top = -1;
	s->size = MAX_CAPACITY;
	return s;
}

void destroy(Stack s)
{
	free(s->contents);
	free(s);
}

void make_empty(Stack s)
{
	s->top = -1;
}

bool is_empty(Stack s)
{
	return s->top == -1;
}

bool is_full(Stack s)
{
	return (s->top == s->size -1);
}

void reallocate(Stack s)
{
	Item *tmp = (Item *)malloc(sizeof(Item) * 2 * s->size);
	if (tmp == NULL) {
		terminate("Error in create: stack could not be created");
	}
	for (int i = 0; i < s->size; i++)
		tmp[i] = s->contents[i];
	free(s->contents);
	s->contents = tmp;
	s->size *= 2;
}

void push(Stack s, Item i)
{
	if (is_full(s))
		reallocate(s);
	s->top++;
	s->contents[s->top] = i;
}

Item pop(Stack s)
{
	if (is_empty(s))
		terminate("Error in pop:stack is empty.");
	s->top--;
	return s->contents[s->top + 1];
}

Item peek(Stack s)
{
	if (is_empty(s))
		terminate("Error in peek: stack is empty.");
	return s->contents[s->top];
}
