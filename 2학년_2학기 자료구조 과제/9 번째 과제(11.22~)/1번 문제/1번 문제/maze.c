#include "maze.h"

void read_maze();
//void print_maze();
bool movable(Position pos, int dir);
int N = 0;

void solve_maze(Stack s)
{
	read_maze();
	Position cur;
	cur.x = 0;
	cur.y = 0;

	for(int i=0;i<N;i++)
		for (int j=0;j<N;j++)
		{
			if (maze[i][j] != 1)continue;
			int size_of_maze = 1;
			cur.x = i;
			cur.y = j;
			while (1) {
				maze[cur.x][cur.y] = VISITED;
				/*if (cur.x == n - 1 && cur.y == n - 1) {
					printf("Found the path.\n");
					break;
				}*/
				bool forwarded = false;
				for (int dir = 0; dir < 8; dir++) {
					if (movable(cur, dir)) {
						size_of_maze++;
						push(s, cur);
						cur = move_to(cur, dir);
						forwarded = true;
						break;
					}
				}
				if (!forwarded) { /* 4������ ��� �����ε� ���� ���ߴٸ� */
					maze[cur.x][cur.y] = BACKTRACKED; /* �Դٰ� �ǵ��ư� ��ġ���� ǥ�� */
					if (is_empty(s)) { /* �ǵ��ư� ��ġ�� ���ٸ� ���� ���� ���� �̷� */
						printf("%d ", size_of_maze);
						break;
					}
					cur = pop(s); /* ���ÿ��� pop�� ��ġ�� ���ο� ������ġ(cur)�� �ȴ�. */
				}
			}
		}
	//print_maze();
}

void read_maze()
{
	FILE *open_maze = fopen("maze.txt", "r");

	fscanf(open_maze, "%d ", &N);	// N�� ���� �б�.

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			fscanf(open_maze, "%d ", &maze[i][j]);
}

bool movable(Position pos, int dir)
{
	Position moved_pos = move_to(pos, dir);
	
	if (moved_pos.x < 0 || moved_pos.y < 0) 
		return false;
	else if (moved_pos.x > 15 || moved_pos.y > 15) 
		return false;									//execption

	if (maze[moved_pos.x][moved_pos.y]==1)
		return true;
	else
		return false;
}