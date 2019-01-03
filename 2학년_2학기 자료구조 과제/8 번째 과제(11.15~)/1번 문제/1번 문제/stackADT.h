#pragma warning (disable:4996)
#ifndef STACKADT_H
#define STACKADT_H
#include <stdbool.h> /* C99 only */

typedef int Item;

typedef struct node {
	Item data;
	int size;
	struct node *next;
}Node;

struct stack_type {
	struct node *top;
};

typedef struct stack_type *Stack;
Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif