#include <stdio.h>
#include "maze.h"

int main()
{
	Stack s = create(); /* �̹����� Position��� �������� �����ϴ� ������ ����Ѵ�. */
	
	solve_maze(s);
}