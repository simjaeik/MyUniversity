#include <stdio.h>
#include <cstdbool>

int N = 8;
int maze[][8] = {
{ 0, 0, 0, 0, 0, 0, 0, 1 },
{ 0, 1, 1, 0, 1, 1, 0, 1 },
{ 0, 0, 0, 1, 0, 0, 0, 1 },
{ 0, 1, 0, 0, 0, 1, 0, 0 },
{ 0, 1, 1, 1, 0, 0, 1, 1 },
{ 0, 1, 0, 0, 0, 1, 0, 1 },
{ 0, 0, 0, 1, 0, 0, 0, 1 },
{ 0, 1, 1, 1, 0, 1, 0, 0 }
};

#define PATHWAY 0 
#define WALL 1 
#define VISITED 2 

int MazePath(int x, int y) {
	int sum = 0;

	if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATHWAY)
		return 0;
	else if (x == N - 1 && y == N - 1) 
		return 1;
	
	else {
		maze[x][y] = VISITED;
		sum += MazePath(x - 1, y);
		sum += MazePath(x, y + 1);
		sum += MazePath(x + 1, y);
		sum += MazePath(x, y - 1);
		maze[x][y] = PATHWAY;

		return sum;
	}
}

int main()
{
	int number = MazePath(0,0);
	printf("%d\n", number);
	return 0;
}