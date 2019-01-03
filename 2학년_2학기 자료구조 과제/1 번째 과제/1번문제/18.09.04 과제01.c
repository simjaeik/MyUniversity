#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define WORDS_NUM 10000
#define BUFFER_SIZE 100

void reset_data(char new_data[]);
int compare_words(char data1[], char data2[]);

char *words[WORDS_NUM];
int words_num[WORDS_NUM] = {0};
char buffer[BUFFER_SIZE];
int cnt = 0;		// words's size

int main()
{
	FILE * open_harry = fopen("harry.txt", "r");
	FILE * to_words = fopen("words.txt", "w");

	// read harry.txt one alphabet until \0 or \n

	while (fscanf(open_harry, "%s", buffer) != EOF)
	{
		if (strlen(buffer) >= 6)
			reset_data(buffer);						// if strlen(buffer) is bigger than 6, store and compare others and array. 
	}

	words[cnt], words_num[cnt] = '\0';
	
	for (int i = 0; i < cnt; i++)
		fprintf(to_words,"%s : %d\n", words[i], words_num[i]);

	fclose(open_harry);	fclose(to_words);

	return 0;
}

void reset_data(char new_data[])
{
	//reset first words
	if (cnt == 0) {
		words[0] = strdup(new_data);		//input the first words
		words_num[0] = 1;
		cnt++;
		return ;
	}
	

	//check data and new_data are same
	for (int i = cnt-1; i >= 0; i--)
	{
		if (!strcmp(new_data, words[i])) {
			words_num[i]++;
			return;											//first, check if words and new_data is same
		}													// match if new and origin are same, cnt ++, else, tmp run
	}

	//move the data
	for (int i = cnt-1; i >= 0; i--)
	{
		if (compare_words(new_data, words[i]) == -1)
		{
			words[i + 1] = words[i];
			words_num[i + 1] = words_num[i];
			if (i == 0)
			{
				words[i] = strdup(new_data);
				words_num[i] = 1;
				return;
			}
		}
		else if (compare_words(new_data, words[i]) == 1)
		{
			words[i + 1] = strdup(new_data);
			words_num[i + 1] = 1;
			cnt++;
			return ;
		}
	}
}

int compare_words(char data1[], char data2[])
{
	int n = 0; 
	
	while (data1[n] != '\0' || data2[n] != '\0')
	{
		if (data1[n] == data2[n])n++;
		else if (data1[n] > data2[n]) return 1;
		else if (data1[n] < data2[n]) return -1;
	}
}