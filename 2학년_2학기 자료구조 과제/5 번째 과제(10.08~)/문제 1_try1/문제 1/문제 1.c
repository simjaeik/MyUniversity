#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20

typedef struct node {
	char *name;
	int count;
	struct node *next;
} Node;

FILE *open_harry;
FILE *open_ignore;

Node *put_and_array_words(Node *firstword, char words[]);
int find_firstword(char ch, Node *Word_lists[]);
int is_word_same(Node *firstword, char words[]);
int is_word_ignore(FILE *fp,char words[]);
void Print_array(Node *head);

int main() {
	Node *Word_lists[26];
	open_harry = fopen("harry.txt", "r");
	open_ignore = fopen("ignore.txt", "r");

	for (int i = 0; i < 26; i++) {						// a~z 배열 만들기
		Word_lists[i] = (Node *)malloc(sizeof(Node));
		Word_lists[i]->name = 97+i;
		Word_lists[i]->count = 0;
		Word_lists[i]->next = NULL;
	}

	char words[BUFFER_SIZE];	
	while (fscanf(open_harry, "%s", words) != EOF) {
		if (is_word_ignore(open_ignore, words) == 1) 
			continue;

		int n = find_firstword(words[0], Word_lists);					//찾은 단어의 첫 글자 주소를 받음
		
		if (is_word_same(Word_lists[n], words) == 1)
			continue;													//if it is same word
		
																	//the words is not in array 
		if (Word_lists[n]->next == NULL) {
			Node *new_data = (Node *)malloc(sizeof(Node));
			new_data->name = words;
			new_data->count = 1;
			Word_lists[n]->next = new_data;
			new_data->next = Word_lists[n]->next;
			continue;
		}
		else if (Word_lists[n]->next->name > words) {
			Node *new_data = (Node *)malloc(sizeof(Node));
			new_data->count = 1;
			new_data->name = words;
			new_data->next = Word_lists[n]->next;
			Word_lists[n]->next = new_data;
			continue;
		}
		else
			Word_lists[n]->next = put_and_array_words(Word_lists[n], words);
		
	}
	Print_array(Word_lists[0]);
	
	return 0;
}

int find_firstword(char ch, Node *Word_lists[]) {
	for (int i = 0; i < 26; i++) {
		if (Word_lists[i]->name == ch)	{
			return i;
		}
	}
	printf("문자가 아닙니다.\n");
	return -1;
}

int is_word_same(Node *firstword, char words[]) {
	if (firstword->next == NULL) 
		return -1;										//if no words in array, return -1;
	Node *p = firstword->next;
	while (p != NULL) {					//if words was in array, count++, return 0
		if (strcmp(p->name, words) == 0) {
			p->count++;
			return 1;
		}
		p = p->next;
	}
	return 0;	//if it is not same
}

int is_word_ignore(FILE *fp,char words[]) {
	char data[BUFFER_SIZE];
	if(strlen(words)<=2)
		return 1;

	while (fscanf(fp, "%s", data) != EOF) {
		if (strcmp(words, data) == 0) {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

Node *put_and_array_words(Node *head, char words[]) {	//during counting

	Node *new_word = (Node *)malloc(sizeof(Node));
	Node *p = head->next;
	Node *prev = NULL;
	while (p->name < words) {
		prev = p;
		p = p->next;
	}
		new_word->next = prev->next;
		prev->next = new_word;
		new_word->count = 1;
		new_word->name = words;
		return 0;
	
}

void Print_array(Node *head) {
	Node *p = head->next;
	while (p != NULL) {
		printf("%s : %d\n", p->name, p->count);
		p= p->next;
	}
}