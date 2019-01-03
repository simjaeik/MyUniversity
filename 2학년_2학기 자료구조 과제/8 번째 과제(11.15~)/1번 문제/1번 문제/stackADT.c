#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

Stack create();
static void terminate(const char *message);
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s); void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

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

void push(Stack s, Item i)
{
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in push: stack is full.");
	new_node->data = i;
	new_node->next = s->top;
	new_node->size = 0;
	s->top = new_node;
}

Item pop(Stack s)
{
	struct node *old_top;
	Item i;
	if (is_empty(s))
		terminate("Error in pop: stack is empty.");
	old_top = s->top;
	i = old_top->data;
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

