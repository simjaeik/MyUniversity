#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX_TERMS 100
#define MAX 100
#define Code_Num 30

int find(char name);
int getmult(int coef, int expo);
void create(char tok);
void add(char name);
void mult(char name);
void calc(char name);
void print(char name);
void diff(char name);

typedef struct term {
	int coef;		//계수
	int expo;		//차수
} Term;

typedef struct polynomial {
	char name;		//이름
	int nbr_terms;	// 다항식을 구성하는 항의 개수
	Term *terms[MAX_TERMS];
}Polynomial;

Polynomial *polys[MAX];
int n;

int main() {
	char code[Code_Num];

	while (1) {
		printf("$ ");
		gets(code);
		char *tok = strtok(code, " ");

		if (strcmp(tok, "create") == 0) {
			tok = strtok(NULL, " ");
			create(*tok);
			continue;
		}
		else if (strcmp(tok, "add") == 0) {
			tok = strtok(NULL, " ");
			add(*tok);
			continue;
		}
		else if (strcmp(tok, "mult") == 0) {
			tok = strtok(NULL, " ");
			mult(*tok);
			continue;
		}
		else if (strcmp(tok, "calc") == 0) {
			tok = strtok(NULL, " ");
			calc(*tok);
			continue;
		}
		else if (strcmp(tok, "print") == 0) {
			tok = strtok(NULL, " ");
			if (strcmp(tok, "all") == 0) {
				for (int i = 0; i < n; i++)
					print(polys[i]->name);
			}
			else print(*tok);
			continue;
		}
		else if (strcmp(tok, "diff") == 0) {
			tok = strtok(NULL, " ");
			diff(*tok);
			continue;
		}
		else if (strcmp(tok, "exit") == 0) return 0;
	}
}

int find(char name) {
	for (int i = 0; i < n; i++) {
		if (name == polys[i]->name) return i;
	}
	return -1;
}

int getmult(int coef, int expo) {		//제곱하기
	int sum = coef;
	int multnum = expo;

	if (expo < 0) multnum = -expo;

	for (int i = 0; i < multnum - 1; i++)
		sum *= coef;

	if (expo < 0)sum = 1 / sum;
	if (expo == 0) return 1;

	return sum;
}

void create(char tok) {
	polys[n] = (Polynomial *)malloc(sizeof(Polynomial));

	polys[n]->name = tok;
	polys[n]->nbr_terms = 0;
	n++;
}

void add(char name) {
	int num = find(name);
	int cnt = polys[num]->nbr_terms;
	int coef = atoi(strtok(NULL, " "));
	int expo = atoi(strtok(NULL, " "));

	if (coef == 0) return;						// coef가 0일때는 무시.
	polys[num]->terms[cnt] = (Term *)malloc(sizeof(Term));

	for (int i = 0; i < cnt; i++) {				// 같은 계수는 차수만 더해준다.
		if (polys[num]->terms[i]->expo == expo) {
			polys[num]->terms[i]->coef += coef;
			return;
		}
	}

	int i = cnt - 1;
	while (i >= 0 && polys[num]->terms[i]->expo < expo) {			//내림차순으로 정렬
		polys[num]->terms[i + 1]->coef = polys[num]->terms[i]->coef;
		polys[num]->terms[i + 1]->expo = polys[num]->terms[i]->expo;
		i--;
	}
	polys[num]->terms[i + 1]->coef = coef;
	polys[num]->terms[i + 1]->expo = expo;
	polys[num]->nbr_terms++;
}

void mult(char name) {
	int num = find(name);
	int cnt = polys[num]->nbr_terms;
	int mult_num = atoi(strtok(NULL, " "));

	for (int i = 0; i < cnt; i++)
		polys[num]->terms[i]->coef *= mult_num;
}

void calc(char name) { // coef가 0일때 생각.								
	int num = find(name);
	int cnt = polys[num]->nbr_terms;
	int mult_num = atoi(strtok(NULL, " "));

	int sum = 0;
	for (int i = 0; i < cnt; i++)
		sum += polys[num]->terms[i]->coef * getmult(mult_num, polys[num]->terms[i]->expo);

	printf("%d\n", sum);
}

void print(char name) {		//coef가 1,-1일때 정의. expo가 1일때 정의
	int num = find(name);
	int cnt = polys[num]->nbr_terms;
	//print all 구현

	if (polys[num]->nbr_terms == 0) {
		printf(" %c(x)=0\n", polys[num]->name);
		return;
	}

	for (int i = 0; i < cnt; i++) {
		if (i == 0)printf(" %c(x) = ", polys[num]->name);
		if (polys[num]->terms[i]->expo == 0) {				//expo가 1일때 (상수항일때)
			printf("%d\n", polys[num]->terms[i]->coef);
			return;
		}

		if (polys[num]->terms[i]->coef == 1) printf("x");	//coef가 1일때
		else if (polys[num]->terms[i]->coef == -1) printf("-x");	//coef가 -1일때
		else if (polys[num]->terms[i]->coef != 1 && polys[num]->terms[i]->coef != -1 && polys[num]->terms[i]->coef != 0)
			printf("%dx", polys[num]->terms[i]->coef);

		if (polys[num]->terms[i]->expo == 1);
		else if (polys[num]->terms[i]->expo != 1 && polys[num]->terms[i]->expo != 0)
			printf("^%d", polys[num]->terms[i]->expo);

		if (i != cnt - 1)printf(" + ");
		else if (i == cnt - 1)printf("\n");
	}
}

void diff(char name) {
	int num = find(name);
	int cnt = polys[num]->nbr_terms;
	char *tok = strtok(NULL, " ");

	if (strcmp(tok, "as") != 0) {
		printf("다시 입력하세요.\n");
		return;
	}
	tok = strtok(NULL, " ");
	create(*tok);

	int num_d = find(*tok);

	for (int i = 0; i < cnt; i++) {
		polys[num_d]->terms[i] = (Term *)malloc(sizeof(Term));
		polys[num_d]->terms[i]->coef = polys[num]->terms[i]->coef * polys[num]->terms[i]->expo;
		polys[num_d]->terms[i]->expo = polys[num]->terms[i]->expo - 1;
		if (polys[num]->terms[i]->expo == 0)cnt--;
	}
	polys[num_d]->nbr_terms = cnt;
}