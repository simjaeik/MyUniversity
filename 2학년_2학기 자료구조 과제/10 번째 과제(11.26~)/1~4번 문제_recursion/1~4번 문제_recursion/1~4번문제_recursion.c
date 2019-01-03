// 1번 문제 - 앞뒤가 같은 단어
//
//#pragma warning (disable:4996)
//#include <stdio.h>
//#include <stdbool.h>
//#include <string.h>
//#define WORD_SIZE 100
//
//bool is_palinrome(char word[], int lenth)
//{
//	if (lenth == 0)
//		return true;
//
//	if (word[lenth - 1] == word[strlen(word) - lenth])
//		is_palinrome(word, lenth - 1);
//	else
//		return false;
//}
//
//int main()
//{
//	char word[WORD_SIZE];
//	scanf("%s", word);
//
//	bool isit_palinrome = is_palinrome(word, (strlen(word) / 2));
//
//	if (isit_palinrome == true) printf("it is palinrome.\n");
//	else if (isit_palinrome == false) printf("it is not palinrome.\n");
//}
//
// 2번 문제 - 사전식 정렬
//
//#pragma warning (disable:4996)
//#include <stdio.h>
//#include <string.h>
//#define LIST_SIZE 100
//
//int compare(char *str1, char *str2)
//{
//	if (str1[0] == '\0'&&str2[0] == '\0')
//		return 0;
//	else if (str1[0] == '\0') return -1;
//	else if (str2[0] == '\0') return 1;
//
//	if (str1[0] < str2[0])
//		return -1;
//	else if (str1[0] > str2[0])
//		return 1;
//
//	compare(str1 + 1, str2 + 1);
//}
//
//int main()
//{
//	int buffer_size = 0; char command[LIST_SIZE];
//	char *WordList[LIST_SIZE];
//
//	while (scanf(" %s", command) != NULL) {
//		if (strcmp(command, "-1") == 0)break;
//		WordList[buffer_size++] = strdup(command);
//	}
//
//	for (int i = 0; i < buffer_size - 1; i++)
//		for (int j = i + 1; j < buffer_size; j++)
//		{
//			if (compare(WordList[i], WordList[j])>0)
//			{
//				char *tmp = WordList[i];
//				WordList[i] = WordList[j];
//				WordList[j] = tmp;
//			}
//		}
//
//	printf("\n알바벳순 정렬\n-------------------------------\n");
//	for (int i = 0; i < buffer_size; i++)
//		printf("%s\n", WordList[i]);
//}
//
// 3번문제 - 합이 K인 친구 구하기 (two-sum)
//
//#pragma warning (disable:4996)
//#include <stdio.h>
//#include<string.h>
//#define MAX 100
//
//int GetSum(int data[], int K, int start, int end, int count)
//{
//	int sum = data[start] + data[end];
//
//	if (start >= end)
//		return count;
//
//	if (sum == K)
//		GetSum(data, K, start + 1, end - 1, count + 1);
//	else if (sum > K)
//		GetSum(data, K, start, end - 1, count);
//	else if (sum < K)
//		GetSum(data, K, start + 1, end, count);
//}
//
//int main()
//{
//	int data[MAX];
//	int N, K;
//	printf("N값을 입력하세요 :");
//	scanf(" %d", &N);
//	int count = 0;
//
//	int start = 0, end = N - 1;
//
//	printf("숫자들을 입력하세요 : ");
//	for (int i = 0; i < N; i++)
//		scanf(" %d", data + i);
//
//	printf("K의 값을 입력하세요 ; ");
//	scanf(" %d", &K);
//
//	int how_many = GetSum(data, K, start, end, count);
//
//	printf("how_many = %d\n", how_many);
//}
//
//
// 4번 문제 - K보다 큰 제일 작은놈, K보다 작은 제일 큰놈 구하기

#pragma warning (disable:4996)
#include <stdio.h>
#define MAX 100

int GetFloor(int data[], int K, int N)
{
	if (N<1) return -1;
	else if (data[N - 1] > K) GetFloor(data, K, N - 1);
	else if (data[N - 1] <= K)return data[N - 1];
}

int GetCeiling(int data[], int K)
{
	if (data[0] == '\0') return -1;
	else if (data[0] < K)GetCeiling((data + 1), K);
	else if (data[0] >= K) return data[0];
}

int main()
{
	int data[MAX];
	int N, K;
	printf("N값을 입력하세요 :");
	scanf(" %d", &N);
	int result = 0;

	int start = 0, end = N - 1;

	printf("숫자들을 입력하세요 : ");
	for (int i = 0; i < N; i++)
		scanf(" %d", data + i);
	data[N] = '\0';

	printf("K의 값을 입력하세요 ; ");
	scanf(" %d", &K);

	int floor = GetFloor(data, K, N);
	int ceiling = GetCeiling(data, K);

	printf("GetFloort = %d\n", floor);
	printf("GetCeiling = %d\n", ceiling);
}
