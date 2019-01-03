#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char * names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

int search(char *name);
void add();
void find();
void status();
void delete();
void load();
void save();
void findall();
void deleteall();

int main()
{
	char buffer[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "add") == 0)
			add();
		else if (strcmp(buffer, "find") == 0)
			find();
		else if (strcmp(buffer, "status") == 0)
			status();
		else if (strcmp(buffer, "delete") == 0)
			delete();
		else if (strcmp(buffer, "save") == 0)
			save();
		else if (strcmp(buffer, "exit") == 0)
			break;
		else if (strcmp(buffer, "deleteall") == 0)
			deleteall();
		else if (strcmp(buffer, "findall") == 0)
			findall();
	}
	return 0;
}

int search(char *name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void load() {
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	fclose(fp);
}

void save() {
	int i;
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);
	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(buf1);
	numbers[i + 1] = strdup(buf2);

	n++;
	printf("%s was added successfully.\n", buf1);
}

void delete() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	int j = index;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);
}

void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person named '%s' exists\n", buf);
	else
		printf("%s\n", numbers[index]);
}

void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);

}

void findall() {
	char find_same[BUFFER_SIZE];
	char cmp_buffer[BUFFER_SIZE];

	scanf("%s", find_same);
	int len = strlen(find_same);
	int person = 0;

	for (int i = 0; i < n; i++) {
		int num = 0;
		strcpy(cmp_buffer, names[i]);
		for (int j = 0; j < len; j++) {
			if (cmp_buffer[j] == find_same[j]) num++;
			else break;
		}
		if (num == len) {
			printf("%s %s\n", names[i], numbers[i]);
			person++;
		}
	}
	printf("%d persons found\n", person);
}
void deleteall() {
	char find_same[BUFFER_SIZE];
	char cmp_buffer[BUFFER_SIZE];

	scanf("%s", find_same);
	int len = strlen(find_same);
	int person = 0, start = 0, deleted = 0;
	char yes_no[5];

	for (int i = 0; i < n; i++) {
		int num = 0;
		strcpy(cmp_buffer, names[i]);
		for (int j = 0; j < len; j++) {
			if (cmp_buffer[j] == find_same[j]) num++;
			else break;
		}
		if (num == len) {
			person++;
			if (person == 1) start = i;
		}
	}
	for (int i = 0; i < person; i++) {
		printf("Do you want to delete '%s' ? ", names[start]);
		scanf("%s", yes_no);
		if (strcmp(yes_no, "yes") == 0) {
			for (int a = start; a < n - 1; a++) {
				names[a] = names[a + 1];
				numbers[a] = numbers[a + 1];
				if (a == n - 2) {
					printf("%s was deleted\n", names[a]);
					deleted++;
					n--;
				}
			}
		}
		else printf("%s was not deleted\n", names[start + i]);
	}
	printf("%d persons are deleted\n", deleted);
}