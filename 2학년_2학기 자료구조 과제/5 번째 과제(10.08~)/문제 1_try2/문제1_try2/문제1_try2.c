#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20


typedef struct node {
	char *name;
	int count;
	struct node *next;
}Node;


int is_ignore(char data[]);
int get_firstword(char ch, Node *Word_lists[]);
int is_same(char data[], Node *head);
Node *add_first(Node *p, char data[]);
void add_middle(Node *head, char data[]);
void Print(Node *head);

int main(void) {
	FILE *open_harry = fopen("harry.txt", "r");

	Node *Word_lists[27];
	Word_lists[26] = '\0';
	for (int i = 0; i < 26; i++) {
		Word_lists[i] = (Node *)malloc(sizeof(Node));
		Word_lists[i]->name = 97 + i;
		Word_lists[i]->count = 0;
		Word_lists[i]->next = NULL;
	}
	
	Node *head_point = Word_lists[0]->next;
	
	char data[BUFFER_SIZE];
	while (fscanf(open_harry, "%s", data) != EOF) {
		if (is_ignore(data) == 1)continue;

		int n = get_firstword(data[0],Word_lists);

		if (is_same(data, Word_lists[n]) == 1)continue;

		if (Word_lists[n]->next == NULL) {					// 첫 번째 배열일때
			Node *new_data = (Node *)malloc(sizeof(Node));
			new_data->name = data;
			new_data->count = 1;
			Word_lists[n]->next = new_data;
			
			while (n < 25 && Word_lists[n + 1] == NULL)n++;
			if (n == 25) { 
				new_data->next = NULL;
				continue;
			}
			new_data->next = Word_lists[n + 1]->next;
			continue;
		}

		if (Word_lists[n]->next->name > data) {
			Word_lists[n]->next = add_first(Word_lists[n],data);
			continue;
		}
		else add_middle(Word_lists[n], data);
	}
	
	Print(head_point);
}

int is_ignore(char data[]) {
	FILE *open_ignore = fopen("ignore.txt", "r");

	if (strlen(data) <= 2) return 1;
	
	char buffer[BUFFER_SIZE];
	while (fscanf(open_ignore, "%s", buffer) != EOF) {
		if (strcmp(data, buffer) == 0)return 1;
	}
	return;
}

int get_firstword(char ch, Node *Word_lists[]) {
	for (int i = 0; i < 26; i++) {
		if (ch == Word_lists[i]->name) return i;
	}
	printf("없을리가 없는데?\n");
}

int is_same(char data[], Node *head) {
	if (head->next == NULL)return;			//처음 오는거라면

	while (data[0] == head->next->name[0]) {
		if (strcmp(data, head->next->name) == 0) {
			head->next->count++;
			return 1;
		}
		head->next = head->next->next;
	}
	return;
}

Node *add_first(Node *p,char data[]) {
	Node *new_data = (Node *)malloc(sizeof(Node));
	new_data->name = data;
	new_data->count = 1;
	new_data->next = p->next;
	return new_data;
}

void add_middle(Node *head,char data[]) {
	Node *new_data = (Node *)malloc(sizeof(Node));
	Node *prev = NULL;
	Node *p = head->next;
	while (p->name > data) {
		prev = p;
		p = p->next;
	}
	new_data->next = prev->next;
	prev->next = new_data;
	new_data->count = 1;
	new_data->name = data;
}

void Print(Node *head) {
	while (head != NULL) {
		printf("%s : %d\n", head->name, head->count);
		head = head->next;
	}
}