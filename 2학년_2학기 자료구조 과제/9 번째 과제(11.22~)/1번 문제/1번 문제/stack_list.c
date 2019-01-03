#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"
#include "pos.h"

static void terminate(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

Stack create()
{
	Stack s = malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create: stack could not be created.");
	s->top = NULL;
	return s;
}

void destroy(Stack s)
{
	make_empty(s);
	free(s);
}

void make_empty(Stack s)
{
	while (!is_empty(s))
		pop(s);
}

bool is_empty(Stack s)
{
	return s->top == NULL;
}

void push(Stack s, Position pos)
{
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in push: stack is full.");
	new_node->pos = pos;
	new_node->next = s->top;
	s->top = new_node;
}

Position pop(Stack s)
{
	struct node *old_top;
	Position i;
	if (is_empty(s))
		terminate("Error in pop: stack is empty.");
	old_top = s->top;
	i = old_top->pos;
	s->top = old_top->next;
	free(old_top);

	return i;
}

Item peek(Stack s)
{
	if (is_empty(s))
		terminate("Error in peek: stack is empty.");
	return s->top->data;
}

