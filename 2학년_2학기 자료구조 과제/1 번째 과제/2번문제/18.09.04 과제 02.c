#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define WORDS_NUM 10000
#define BUFFER_SIZE 100

void reset_data(char new_data[]);
int compare_words(char data1[], char data2[]);
void run_hangman(char data[], int lenth);

char *words[WORDS_NUM];
char buffer[BUFFER_SIZE];
int cnt = 0;

int main()
{
	FILE * open_harry = fopen("harry.txt", "r");

	while (fscanf(open_harry, "%s", buffer) != EOF)
		if (strlen(buffer) >= 6)
			reset_data(buffer);
	
	words[cnt] = '\0';
	
	char Y_N = 'y';

	while (1) {
		srand(time(NULL));
		int r_num = (rand() % cnt) - 1;
		char *rand_word = words[r_num];			//get random word

		run_hangman(rand_word,strlen(rand_word));				//

		printf("Try again? (Y/N):");
		scanf(" %c", &Y_N);
		printf("\n");

		if (Y_N == 'N' || Y_N == 'n') break;
	}

	fclose(open_harry);

	return 0;
}

void reset_data(char new_data[])
{
	if (cnt == 0) {
		words[0] = strdup(new_data);		
		cnt++;
		return ;
	}
	
	for (int i = cnt-1; i >= 0; i--)
		if (!strcmp(new_data, words[i])) 
			return;											
															
	for (int i = cnt-1; i >= 0; i--)
	{
		if (compare_words(new_data, words[i]) == -1)
		{
			words[i + 1] = words[i];
			if (i == 0)
			{
				words[i] = strdup(new_data);
				return;
			}
		}
		else if (compare_words(new_data, words[i]) == 1)
		{
			words[i + 1] = strdup(new_data);
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

void run_hangman(char data[],int lenth)
{
	int check[BUFFER_SIZE] = { 0 };
	char guess_word;

	while (1)
	{
		int count = 0;

		printf("Guess an alphabet : ");
		scanf(" %c", &guess_word);

		for (int i = 0; i < lenth; i++)
			if (check[i]!=1 && data[i] == guess_word) 
			{													// check guess_word and data are correct
				check[i] = 1;
				break;
			}

		printf("\n     ");

		for (int i = 0; i < lenth; i++)
		{
			if (check[i] == 1) { 
				printf("%c", data[i]);
				count++;
			}
			else if (check[i] == 0)printf("*");
		}

		printf("\n\n");

		if (count == lenth) return;				//correct the word.
	}
}