
#include "string_toos.h"


int read_line(FILE *fp,char str[], int n){
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n'&& ch != EOF)
		if (i < n - 1)
			str[i ++] = ch;

	str[i] = '\0';
	return i;
}