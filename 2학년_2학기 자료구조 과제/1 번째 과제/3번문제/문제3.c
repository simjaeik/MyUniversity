#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_SIZE 10000

void count_lenth(char ch);

char *data[DATA_SIZE];
int n, m;
int is_W=0,cnt=0,lenth = 0,is_space=0,first=0,n=0;

int main()
{
	char space = ' '; char enter = '\n';
	FILE *open_tabular = fopen("tabular.txt", "r");
	FILE *write_output = fopen("output.txt", "w");

	fscanf(open_tabular, "%d %d ", &n, &m);

	char word;
	while ((word = fgetc(open_tabular)) != EOF)
		count_lenth(word);

	data[n] = '\0';
	int is_W = 0, cnt = 1, is_space = 0, first = 0,n=4;

	while (data[n++] != '\0')
	{
		if (is_space == 1 && data[n] == ' ') {
			fputc(space,write_output);
			cnt++;
			is_space = 0;
			continue;
		}
		else if (is_space == 0 && data[n] == ' ')continue;

		if (data[n] == '&') {
			for (int i = cnt; i <= lenth; i++) fputc(space,write_output);
			cnt = 0;
			is_space = 0;
			continue;
		}
		else if (data[n] == '\\') {
			if (is_W == 1) {
				is_W = 0;
				continue;
			}
			for (int i = cnt; i <= lenth; i++) fputc(space, write_output);
			is_W = 1;
			cnt = 0;
			is_space = 0;
			fputc(enter,write_output);
			continue;
		}
		else if (data[n] != '\n') {
			fputc(data[n],write_output);
			is_space = 1;
			cnt++;
		}
	}

	fclose(open_tabular); fclose(write_output);
}

void count_lenth(char ch)
{
	data[n++] = ch;
	//단어 뒤에 나오는 공백이 아니면 전부 무시, 그리고 공백 다음 공백도 무시
	if (is_space == 1 && ch == ' ') {
		cnt++;
		is_space = 0;
		return;
	}
	else if (is_space == 0 && ch == ' ')return;

	if (ch == '&') {
		if (lenth < cnt) lenth = cnt;
		cnt = 0;
		is_space = 0;
		return;
	}
	else if (ch == '\\') {
		if (lenth < cnt) lenth = cnt;
		if (is_W == 1) {
			is_W = 0;
			return;
		}

		is_W = 1;
		cnt = 0;
		is_space = 0;
		return;
	}
	else if (ch != '\n') {
		cnt++;
		is_space = 1;
	}
}

