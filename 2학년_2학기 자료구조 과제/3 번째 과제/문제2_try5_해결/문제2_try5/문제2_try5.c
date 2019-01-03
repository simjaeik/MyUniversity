#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 100

char ch;
char word[BUFFER_SIZE];
char *words[BUFFER_SIZE];

int cnt = 0, sum = 0, n = 0,count=0;
void get_line(int words_size, int words_num,FILE *w_fp);
FILE *o_fp; FILE *w_fp;

int main() {
	o_fp = fopen("harry.txt", "r");
	w_fp = fopen("aligned.txt", "w");

	while ((ch = fgetc(o_fp)) != EOF) {
		if (!isspace(ch)) word[cnt++] = ch;

		else if (isspace(ch)) {
			if (cnt != 0) {
				word[cnt] = '\0';
				words[n++] = strdup(word);
				sum += cnt;
				get_line(cnt, n, w_fp);
				cnt = 0;
			}

			if (ch == '\n') {
				ch = fgetc(o_fp);
				if (ch == '\n') {
					for (int i = 0; i < n; i++) {
						fprintf(w_fp, "%s", words[i]);
						if (i != cnt) fprintf(w_fp, " ", stdin);
					}
					fprintf(w_fp, "\n\n", stdin);
					count = 0;
					n = 0;
					sum = 0;
				}
				else if (!isspace(ch)) word[cnt++] = ch;
			}
		}
	}

	fclose(o_fp);
	fclose(w_fp);
}

void get_line(int words_size, int words_num, FILE *w_fp) {
	
	if (sum < 80) {
		sum++;
		return;
	}
	else if (sum == 80) {
		for (int i = 0; i < words_num; i++) {
			fprintf(w_fp, "%s", words[i]);
			if (i != words_num) fprintf(w_fp, " ", stdin);
		}
		fprintf(w_fp,"\n",stdin);
		n = 0;
		sum = 0;
		return;
	}
	else if (sum > 80) {
		int space = 81 - (sum - words_size);
		for (int i = 0; i < words_num - 1; i++) {
			fprintf(w_fp, "%s", words[i]);
			if (i == (words_num - 2)) {
				fprintf(w_fp,"\n",stdin);
				continue;
			}
			fprintf(w_fp, " ", stdin);
			for (int j = space; i < j; j = j - words_num) fprintf(w_fp, " ", stdin);
		}
		words[0] = words[words_num - 1];
		sum = strlen(words[words_num - 1]) + 1;
		n = 1;
		return;
	}
}