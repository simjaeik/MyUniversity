#ifndef STACKADT_H
#define STACKADT_H
#include "pos.h"
#include <stdbool.h> /* C99 only */

typedef int Item;

struct node {
	Item data;
	Position pos;
	struct node *next;
};

struct stack_type {
	struct node *top;
};
typedef struct stack_type *Stack;

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
void push(Stack s, Position pos);
Position pop(Stack s);
Item peek(Stack s);

#endif