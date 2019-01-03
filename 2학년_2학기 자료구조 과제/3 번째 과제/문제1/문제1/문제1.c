#pragma warning (disable:4996)
#include <stdio.h>
#define BUFFER_SIZE 100
#define IP_SIZE 4
char get_ip[BUFFER_SIZE];
char *ip = get_ip;
int n = 0;

int num_level(int num);
int check_ip(char *buffer);

int main() {
	printf("IP주소를 입력하세요 : ");
	scanf("%s", get_ip);
	
	for (int i = 0; i < 4; i++) {
		if (check_ip(atoi(ip+n)) == 0) {
			printf("No.\n");
			return 0;
		}
	}
	printf("Yes.\n");
	return 0;
}

int check_ip(char *buffer) {
	if (buffer >= 0 && buffer <= 255) {
		n += num_level(buffer)+1;
		return 1;
	}
	else return 0;
}

int num_level(int num) {
	int position = 1;
	while (num / 10 != 0) {
		num /= 10;
		position++;
	}
	return position;
}