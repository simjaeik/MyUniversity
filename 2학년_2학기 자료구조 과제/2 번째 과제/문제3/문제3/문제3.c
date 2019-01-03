#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

char *data[BUFFER_SIZE];
char buffer[BUFFER_SIZE];

int n =0,buffer_sum=0;
int main() {
	FILE *read_harry = fopen("harry.txt", "r");
	FILE *arr_aligned = fopen("aligned.txt", "w");

	int n = 0;	
	while (fscanf(read_harry, "%s", buffer) != EOF) {
		if (buffer_sum < 81) {
			buffer_sum += strlen(buffer) + 1;
			data[n++] = strdup(buffer);
		}
		else if (buffer_sum == 81) {
			int i = 0;
			while (1) {
				if (i < n-1)  fprintf(arr_aligned, "%s ", data[i++]); 
				else if (i = n-1) {
					fprintf(arr_aligned, "%s\n", data[i]);
					buffer_sum = strlen(buffer)+1;
					data[0] = strdup(buffer);
					n = 1;	i = 0;
					break;
				}
			}
		}
		if (buffer_sum > 81) {
			int space = 82 - (buffer_sum - strlen(buffer)); int i = 0;
			while (1) {
				if (i < n - 2) {
					fprintf(arr_aligned, "%s ", data[i++]);
					for (int a = space; a >= i; a = a - n) {
						fprintf(arr_aligned, " ", stdin);
					}
				}
				else if (i = n - 2) {
					fprintf(arr_aligned, "%s\n", data[i]);
					data[0] = data[i+1];
					buffer_sum = strlen(data[0])+1;			
					n = 1;	i = 0;
					break;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		fprintf(arr_aligned, "%s ", data[i]);
	fprintf(arr_aligned, "%s", data[n]);

	fclose(read_harry); fclose(arr_aligned);

	return 0;
}