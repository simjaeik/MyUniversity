#pragma warning (disable:4996)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define WORD_SIZE 100

bool is_palinrome(char word[], int lenth)
{
	if (lenth == 0)
		return true;
	
	if (word[lenth-1] == word[strlen(word) - lenth])
		is_palinrome(word, lenth - 1);
	else
		return false;
}

int main()
{
	char word[WORD_SIZE];
	scanf("%s", word);
	
	bool isit_palinrome = is_palinrome(word,(strlen(word)/2));

	if (isit_palinrome == true) printf("it is palinrome.\n");
	else if (isit_palinrome == false) printf("it is not palinrome.\n");
}