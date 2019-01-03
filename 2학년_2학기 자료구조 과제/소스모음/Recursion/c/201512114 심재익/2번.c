#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define LIST_SIZE 100

int compare(char *str1, char *str2)
{
	if (str1[0] == '\0'&&str2[0] == '\0')
		return 0;
	else if (str1[0] == '\0') return - 1;
	else if (str2[0] == '\0') return 1;

	if (str1[0] < str2[0])
		return -1;
	else if(str1[0] > str2[0])
		return 1;
	
	compare(str1 + 1, str2 + 1);
}

int main()
{
	int buffer_size = 0; char command[LIST_SIZE];
	char *WordList[LIST_SIZE];

	while (scanf(" %s", command) != NULL){
		if (strcmp(command, "-1") == 0)break;
		WordList[buffer_size++] = strdup(command);
	}

	for (int i = 0; i < buffer_size-1; i++)
		for (int j = i+1; j < buffer_size; j++)
		{
			if (compare(WordList[i], WordList[j])>0)
			{
				char *tmp = WordList[i];
				WordList[i] = WordList[j];
				WordList[j] = tmp;
			}
		}
	
	printf("\n�˹ٺ��� ����\n-------------------------------\n");
	for (int i = 0; i < buffer_size; i++)
		printf("%s\n", WordList[i]);
}
