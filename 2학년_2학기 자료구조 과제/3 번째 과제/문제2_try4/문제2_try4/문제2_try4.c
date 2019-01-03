#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 100
/* 한 글자씩 받아내고 공백 나올때까지 읽는다. 그리고 한단어씩 저장한 후 그때까지의 크기도 저장,
   그중에서 \n이 두번 나오면 출력해버리고 \n 두번 하기. 그리고 공백이 나올때 space=1로 둬서 다른 공백들은 무시하게 만들기.*/
char ch;
char word[BUFFER_SIZE];
char table[81];
char *words[BUFFER_SIZE];

int cnt = 0, sum = 0, n = 0;
void get_line(int words_size, int words_num);
FILE *o_fp;
FILE *w_fp;

int main() {
	FILE *o_fp = fopen("harry.txt", "r");
	if (o_fp == NULL){
		printf("o_fp파일을 열 수 없음.\n");
		fclose(o_fp);
		return;
	}
	FILE *w_fp = fopen("aligned.txt", "w");
	if (w_fp == NULL) {
		printf("w_fp파일을 열 수 없음.\n");
		fclose(w_fp);
		return ;
	}

	while ((ch = fgetc(o_fp)) != EOF) {
		if (!isspace(ch)) word[cnt++] = ch;

		else if (isspace(ch)) {
			if (cnt != 0) {
				word[cnt] = '\0';
				words[n++] = strdup(word);
				sum += cnt;	
				get_line(cnt,n);
				cnt = 0;
			}
			if (ch == '\n') {
				ch = fgetc(o_fp);
				if (ch == '\n') {
					get_line(cnt, n);
					fprintf(w_fp, "\n", stdin);
				}
				else if (!isspace(ch)) word[cnt++] = ch;
			}
		}
	}

}

void get_line(int words_size, int words_num) {
	FILE *w_fp = fopen("aligned.txt", "w");
	if (w_fp == NULL) {
		printf("w_fp파일을 열 수 없음.\n");
		fclose(w_fp);
		return;
	}

	if (sum < 80) {
		sum++;		

		return;
	}
	else if (sum == 80) {
		for (int i = 0; i < words_num; i++) {				
			fprintf(w_fp,"%s ", words[i]);
			//strcat(table, words[i]);
			if (i == words_num-1) fprintf(w_fp, "%s\n", stdin); 
				//strcat(table, " ");
		}
		//fprintf(w_fp, "%s\n", table);
		n = 0;	sum = 0;
		return; 
	}
	else if (sum > 80) {
		int space = 81 - (sum - words_size);
		for (int i = 0; i < words_num - 1; i++) {
			fprintf(w_fp, "%s ", words[i]);
			//strcat(table, words[i]);
			if (i == (words_num - 2)) fprintf(w_fp,"\n",stdin);
			//	strcat(table, " ");
			for (int j = space; i < j; j = j - words_num) fprintf(w_fp, " ", stdin);
				//strcat(table, " ");
		}
		//fprintf(w_fp, "%s!\n", table);
		words[0] = words[words_num-1];
		sum = strlen(words[words_num-1]) + 1;
		n = 1;
		return;
	}
	
}