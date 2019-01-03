#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

int main() {
	char data[] = "Hello world it is beutiful ! I like it, good~";
	
	char *token = strtok(data, " ,");
	while (token != NULL) {
		printf("token : %s\n", token);
		printf("\n%s\n", data);
		token = strtok(NULL, " ,");
	}
	return 0;
}