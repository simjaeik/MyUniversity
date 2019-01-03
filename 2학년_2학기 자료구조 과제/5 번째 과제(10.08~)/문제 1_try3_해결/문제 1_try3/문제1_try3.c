#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFFER_SIZE 30

typedef struct node {
	char *name;
	int count;
	struct node *next;
}Node;

void Print(Node *head);
void *add_middle(char *data, Node *head);
Node *get_first(char *data, Node *head);
Node *add_first(char data[]);
int is_same(char *data, Node *p);
int get_firstword(char ch, Node *p[]);
int ignore(char *data,FILE *open_ignore);
FILE *open_ignore;

int main(void) {
	FILE *open_harry = fopen("harry.txt", "r");
	open_ignore=fopen("ignore.txt", "r");
	Node *Word_lists[27];

	for (int i = 0; i < 26; i++) {
		Word_lists[i]=(Node *)malloc(sizeof(Node));
		Word_lists[i]->count = 0;
		Word_lists[i]->name = (97 + i);
		Word_lists[i]->next = NULL;
	}

	char word[BUFFER_SIZE];
	while (fscanf(open_harry, "%s", word) != EOF) {
		if (ignore(word,open_ignore) == 1)continue;
		int n = get_firstword(word[0],Word_lists);
		if (is_same(word,Word_lists[n]->next) == 1)continue;

		if (Word_lists[n]->next == NULL) {				//그 알파벳으로 시작하는 단어가 처음올때
			Word_lists[n]->next = add_first(word);
		}
		else if (Word_lists[n]->next->name > word) {	//제일 작은 단어일때
			Word_lists[n]->next = get_first(word,Word_lists[n]);
		}
		else 
		{
			add_middle(word, Word_lists[n]->next);
		}
	}
	for (int i = 0; i < 26; i++) {
		Print(Word_lists[i]);
	}
}
int ignore(char *data,FILE *open_ignore) {
	
	char buffer[BUFFER_SIZE];

	if (strlen(data) <= 2)return 1;

	while (fscanf(open_ignore, "%s", buffer) != EOF)
		if (strcmp(buffer, data) == 0)
			return 1;

	return 0;
}

int is_same(char *data,Node *p) {
	while (p != NULL) {
		if (strcmp(p->name, data) == 0) {
			p->count++;
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int get_firstword(char ch,Node *p[]) {
	for (int i = 0; i < 26; i++)
		if (ch == p[i]->name)
			return i;
}

Node *add_first(char data[]) {
	Node *new_data = (Node *)malloc(sizeof(Node));
	new_data->count = 1;
	new_data->name = (char *)malloc(sizeof(char)*strlen(data+1));
	strcpy(new_data->name, data);
	new_data->next = NULL;

	return new_data;
}

Node *get_first(char *data, Node *head) {
	Node *new_data = (Node *)malloc(sizeof(Node));
	new_data->next = head->next;
	new_data->count = 1;
	new_data->name = (char *)malloc(sizeof(char)*strlen(data + 1));
	strcpy(new_data->name, data);

	return new_data;
}

void *add_middle(char *data, Node *head) {
	Node *new_data = (Node *)malloc(sizeof(Node));
	Node *prev = NULL;

	while (head->name != NULL && data > head->name) {
		prev = head;
		head = head->next;
	} 
	new_data->next = prev->next;
	prev->next = new_data;
	new_data->count = 1;
	new_data->name = (char *)malloc(sizeof(char)*strlen(data + 1));
	strcpy(new_data->name, data);
}

void Print(Node *head) {
	Node *p = head->next;
	while (p != NULL) {
		printf("%s : %d\n", p->name, p->count);
		p = p->next;
	}
}