#include <stdio.h>
#include "maze.h"

int main()
{
	Stack s = create(); /* 이번에는 Position대신 정수들을 저장하는 스택을 사용한다. */
	
	solve_maze(s);
}