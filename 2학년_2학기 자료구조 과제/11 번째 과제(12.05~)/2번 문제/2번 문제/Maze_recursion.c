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
