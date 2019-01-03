#ifndef MAZE_H
#define MAZE_H
#pragma warning (disable:4996)

#include <stdio.h>
#include "stackADT.h"
#include "pos.h"

#define MAX 100
#define WALL 0 /* ������ �� �ִ� ��ġ */
#define PATH 1 /* ������ �� ���� ��ġ */
#define VISITED 2 /* �̹� �湮�� ��ġ */
#define BACKTRACKED 3 /* �湮�ߴٰ� �ǵ��� ���� ��ġ */
int maze[MAX][MAX];
int n; /* �̷��� ũ�� */

#pragma warning (disable:4996)

void read_maze();
void solve_maze(Stack s);
//void print_maze();
bool movable(Position pos, int dir);

#endif