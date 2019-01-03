#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 100

char *arr_word[BUFFER_SIZE];
char buffer[BUFFER_SIZE];
int sum = 0, cnt = 0;

int main() {
	FILE *open_harry = fopen("harry.txt", "r");
	FILE *get_aligned = fopen("aligned.txt", "w");

	char ch[2]; int ch_n = 0; char buf[2];
	while (fscanf(open_harry, "%s", buffer) != EOF) {

		ch[0] = fgetc(open_harry);
		ch[1] = '\0';
		if (ch[0] == '\n') {
			ch[0] = fgetc(open_harry);
			ch[1] = '\0';
			if (ch[0] == '\n') {
				arr_word[cnt] = strdup(buffer);
				sum += strlen(buffer) + 1;
				if (sum < 81) {
					for (int i = 0; i <= cnt; i++) {
						if (i == cnt) {
							fprintf(get_aligned, "%s\n\n", arr_word[i]);
							cnt = 0; sum = 0;
							continue;
						}
						fprintf(get_aligned, "%s ", arr_word[i]);
					}
				}
				else if (sum == 81)	{
					for (int i = 0; i < cnt; i++) {
						if (i == cnt - 1) {
							fprintf(get_aligned, "%s 2\n", arr_word[i], sum);
							cnt = 0; sum = 0;
							continue;
						}
						fprintf(get_aligned, "%s ", arr_word[i]);
					}
				}
				else if (sum > 81) {
					int space = 82 - (sum - strlen(buffer));
					for (int i = 0; i < cnt - 1; i++) {
						if (i == cnt - 2) {
							fprintf(get_aligned, "%s 1\n", arr_word[i], sum);
							sum = strlen(buffer) + 1;
							cnt = 0;
							continue;
						}
						fprintf(get_aligned, "%s ", arr_word[i]);

						for (int a = space; a > i; a = a - cnt)
							fprintf(get_aligned, " ", stdin);
					}

				}
			}
			else {
				arr_word[cnt++] = strdup(buffer);
				sum += strlen(buffer) + 1;
				ch_n = 1;
				strcpy(buf, ch);
				if (sum < 80)
					continue;
			}
		}

		if (ch_n == 1) {
			strcat(buf, buffer);
			arr_word[cnt++] = strdup(buf);
			sum += strlen(buffer) + 2;
			ch_n = 0;
		}
		else if (sum < 81) {
			arr_word[cnt++] = strdup(buffer);
			sum += strlen(buffer)+1;
		}
		
		if (sum == 81) {
			for (int i = 0; i < cnt; i++) {
				if (i == cnt - 1) {
					fprintf(get_aligned,"%s 2\n", arr_word[i],sum);
					cnt = 0; sum = 0;
					continue;
				}
				fprintf(get_aligned,"%s ", arr_word[i]);
			}
			continue;
		}
		else if (sum > 81) {
			int space = 82 - (sum - strlen(buffer));
			for (int i = 0; i < cnt - 1; i++) {
				if (i == cnt - 2) {
					fprintf(get_aligned, "%s 1\n", arr_word[i],sum);
					sum = strlen(buffer) + 1;
					arr_word[0] = strdup(buffer);
					cnt = 1;
					continue;
				}
				fprintf(get_aligned, "%s ", arr_word[i]);

				for (int a = space; a > i; a = a - cnt)
					fprintf(get_aligned, " ", stdin);
			}
			continue;
		}

	}
}