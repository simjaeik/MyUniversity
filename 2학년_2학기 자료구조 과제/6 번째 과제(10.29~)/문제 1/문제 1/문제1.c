#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_POLYS 100
#define BUFFER_LENGTH 100

typedef struct term {
	int coef;
	int expo;
	struct term *next;
}Term;

typedef struct polynomial {
	char name;
	Term *first;
	int size;
}Polynomial;

Polynomial *polys[MAX_POLYS];
int n = 0;

int read_line(FILE *fp, char str[], int limit);
Term *create_term_instance();
Polynomial *create_polynomial_instance(char name);
void add_term(int c, int e, Polynomial *poly);
int eval(Polynomial *poly, int x);
int eval_sum(Term *term, int x);
void print_poly(Polynomial *p);
void print_term(Term *pTerm/*, int *count*/);
void handle_definition(char *expression);
void process_command();
void handle_print(char name);
void printall();
void handle_calc(char name, char *x_str);
void erase_blanks(char *expression);
Polynomial *create_by_parse_polynomial(char name, char *body);
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly);
void insert_polynomial(Polynomial *ptr_poly);
void destroy_polynomial(Polynomial *ptr_poly);
Polynomial *create_by_add_two_polynomial(char name, char f, char g);
Polynomial *create_by_multi_two_polynomials(char name, char f, char g); 
Polynomial *multi_function(Polynomial *main_func, Polynomial *p, Polynomial *q);
Term *multi_one(Term *p, Term *q);

int main(void) {
	process_command();
}

int read_line(FILE*fp, char str[], int limit) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < limit) {
			str[i] = ch;
			i++;
		}
	}
	str[i] = '\0';
	return i;
}

Term *create_term_instance() {
	Term *t = (Term *)malloc(sizeof(Term));
	t->coef = 0;
	t->expo = 0;
	t->next = NULL;
	return t;
}

Polynomial *create_polynomial_instance(char name) {
	Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}

void add_term(int c, int e, Polynomial *poly) {		// 다항식을 하나씩 받아 내림차순으로 정렬한다.
	if (c == 0)
		return;
	Term *p = poly->first, *q = NULL;
	while (p != NULL && p->expo > e) {
		q = p;
		p = p->next;
	}

	if (p != NULL && p->expo == e) {
		p->coef += c;
		if (p->coef == 0) {
			if (q = NULL)
				poly->first = p->next;
			else
				q->next = p->next;
			poly->size--;
			free(q);
		}
		return;
	}
	Term *term = create_term_instance();
	term->coef = c;
	term->expo = e;

	if (q == NULL) {
		term->next = poly->first;
		poly->first = term;
	}
	else {
		term->next = p;
		q->next = term;
	}
	poly->size++;
}

int eval(Polynomial *poly, int x) {		// 다항식 계산 f(x)
	int result = 0;
	Term *t = poly->first;
	while (t != NULL) {
		result += eval_sum(t, x);
		t = t->next;
	}
	return result;
}

int eval_sum(Term *term, int x) {
	int result = term->coef;
	for (int i = 0; i < term->expo; i++) {
		result *= x;
	}
	return result;
}

void print_poly(Polynomial *p) {
	printf("%c=", p->name);
	Term *t = p->first;
	while (t != NULL) {
		print_term(t);
		if (t->next != NULL && t->next->coef > 0)
			printf("+");
		t = t->next;
	}
	printf("\n");
}

void print_term(Term *pTerm) {					//수정해야함(예외사항)
	if (pTerm->expo == 0) {
		printf("%d", pTerm->coef);
	}
	else if (pTerm->coef == 1) {
		if (pTerm->expo == 1) {
			printf("x");
			return;
		}
		printf("x^%d", pTerm->expo);
	}
	else if (pTerm->coef == -1) {
		if (pTerm->expo == 1) {
			printf("-x");
			return;
		}
		printf("-x^%d", pTerm->expo);
	}
	else if (pTerm->expo == 1) {
		printf("%dx", pTerm->coef);
	}
	else {
		printf("%dx^%d", pTerm->coef, pTerm->expo);
	}
}

void process_command() {
	char command_line[BUFFER_LENGTH];
	char copied[BUFFER_LENGTH];
	char *command, *arg1, *arg2;

	while (1) {
		printf("& ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;
		strcpy(copied, command_line);
		command = strtok(command_line, " ");
		if (strcmp(command, "print") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_print(arg1[0]);
		}
		else if (strcmp(command, "printall") == 0) {
			printall();
		}
		else if (strcmp(command, "calc") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			handle_definition(copied);
		}
	}
}

void handle_print(char name) {
	int i = 0;
	while (polys[i] != NULL) {
		if (polys[i]->name == name) {
			print_poly(polys[i]);
			return;
		}
		i++;
	}
	printf("There is no %c function.\n", name);
	return;
}

void printall() {
	if (n == 0)
		printf("There is no function.\n");
	for (int i = 0; i < n; i++) {
		print_poly(polys[i]);
	}
	return;
}

void handle_calc(char name, char *x_str) {
	int i = 0;
	int num = atoi(x_str);
	while (polys[i] != NULL) {
		if (polys[i]->name == name) {
			int result=eval(polys[i],num);
			printf("%d\n", result);
			return;
		}
		i++;
	}
	printf("There is no %c function.\n", name);
	return;
}

void handle_definition(char *expression) {
	erase_blanks(expression);

	char *f_name = strtok(expression, "=");
	if (f_name == NULL || strlen(f_name) != 1) {
		printf("Unsupported command.\n");
		return;
	}

	char *exp_body = strtok(NULL, "=");
	if (exp_body == NULL || strlen(exp_body) <= 0) {
		printf("Invalid expression format.\n");
		return;
	}
	if (exp_body[0] >= 'a'&&exp_body[0] <= 'z'&&exp_body[0] != 'x') {
		if (exp_body[1] == '+') {
			char *former = strtok(exp_body, "+");
			if (former == NULL || strlen(former) != 1) {
				printf("Invalid expression format.\n");
				return;
			}
			char *later = strtok(NULL, "+");
			if (later == NULL || strlen(later) != 1) {
				printf("Invalid expression format.\n");
				return;
			}
			Polynomial *pol = create_by_add_two_polynomial(f_name[0], former[0], later[0]);
			if (pol == NULL) {
				printf("Invalid expression format.\n");
				return;
			}
			insert_polynomial(pol);
		}
		else if (exp_body[1] == '*') {
			char *former = strtok(exp_body, "*");
			if (former == NULL || strlen(former) != 1) {
				printf("Invalid expression format.\n");
				return;
			}
			char *later = strtok(NULL, "*");
			if (later == NULL || strlen(later) != 1) {
				printf("Invalid expression format.\n");
				return;
			}
			Polynomial *pol = create_by_multi_two_polynomials(f_name[0], former[0], later[0]);
			if (pol == NULL) {
				printf("Invalid expression format.\n");
				return;
			}
			insert_polynomial(pol);
		}
	}
	else {
		Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
		if (pol == NULL) {
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
}

void erase_blanks(char *expression) {
	int head = 0; int train = 0;
	while (train != strlen(expression)) {
		if (!isspace(expression[train])) {
			expression[head] = expression[train];
			train++;
			head++;
		}
		else
		train++;
	}
	expression[head] = '\0';
}

Polynomial *create_by_parse_polynomial(char name, char *body) {
	Polynomial *ptr_poly = create_polynomial_instance(name);

	int i = 0, begin_term = 0;
	while (i < strlen(body)) {
		if (body[i] == '+' || body[i] == '-')
			i++;
		while (i < strlen(body) && body[i] != '+' && body[i] != '-')
			i++;
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if (result == 0) {
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;

	if (expr[i] == '+')
		i++;
	else if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}
	if (coef == 0)
		coef = sign_coef;
	else
		coef *= sign_coef;

	if (i >= end) {
		add_term(coef, 0, p_poly);
		return 1;
	}

	if (expr[i] != 'x')
		return 0;
	i++;

	if (i >= end) {
		add_term(coef, 1, p_poly);
		return 1;
	}

	if (expr[i] != '^')
		return 0;
	i++;

	expo = 0;
	while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}

	add_term(coef, expo, p_poly);
	return 1;
}

void insert_polynomial(Polynomial *ptr_poly) {
	for (int i = 0; i < n; i++) {
		if (polys[i]->name == ptr_poly->name) {
			destroy_polynomial(polys[i]);
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[n++] = ptr_poly;
}
void destroy_polynomial(Polynomial *ptr_poly) {
	if (ptr_poly == NULL)
		return;
	Term *t = ptr_poly->first, *tmp;
	while (t != NULL) {
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}

Polynomial *create_by_add_two_polynomial(char name, char f, char g) {
	int count = 0; int i = 0; int j = 0;
	while (polys[i]->name != f)i++;
	while (polys[j]->name != g)j++;
	if (i >= n || j >= n) {
		printf("There is no function.\n");
		return;
	}

	if (name == f) {
		Term *p = polys[j]->first;
		while (p != NULL) {
			add_term(p->coef, p->expo, polys[i]);
			p = p->next;
		}
		return;
	}
	else if (name == g) {
		Term *p = polys[i]->first;
		while (p != NULL) {
			add_term(p->coef, p->expo, polys[j]);
			p = p->next;
		}
		return;
	}

	Polynomial *sumed_func = create_polynomial_instance(name);
	Term *p = polys[i]->first;
	Term *q = polys[j]->first;
	while (p != NULL) {
		add_term(p->coef, p->expo, sumed_func);
		p = p->next;
	}
	while (q != NULL) {
		add_term(q->coef, q->expo, sumed_func);
		q = q->next;
	}
	return sumed_func;
}

Polynomial *create_by_multi_two_polynomials(char name, char f, char g)
{
	int count = 0; int i = 0; int j = 0;
	while (polys[i]->name != f)i++;
	while (polys[j]->name != g)j++;
	if (i >= n || j >= n) {
		printf("There is no function.\n");
		return;
	}

	Polynomial *multed_func = create_polynomial_instance(name);
	multed_func = multi_function(multed_func, polys[i], polys[j]);
	
	return multed_func;
}

Term *multi_one(Term *p,Term *q) {
	Term *multed = create_term_instance();

	multed->coef =( p->coef)*(q->coef);
	multed->expo = (p->expo) + (q->expo);
	multed->next = NULL;

	return multed;
}

Polynomial *multi_function(Polynomial *main_func,Polynomial *p, Polynomial *q) {
	Term *first_p = p->first;
	Term *first_q = q->first;
	Term *c = NULL;

	while (first_p != NULL) {
		while (first_q != NULL) {
			c=multi_one(first_p, first_q);
			add_term(c->coef, c->expo, main_func);

			first_q = first_q->next;
		}
		first_p = first_p->next;
		first_q = q->first;
	}
	return main_func;
}