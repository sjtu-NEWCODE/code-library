int const N = , M = , G = ;
struct node {
	int col, row, left, right, up, down;
	inline void clear() { col = row = left = right = up = down = 0; }
} grid[G];
int n, m, tot;
int cnt[M], head[N], tail[N];
inline void prepare() {
	tot = m + 1;
	for (int i = 1; i <= n; ++i) head[i] = tail[i] = 0;
	for (int i = 1; i <= m + 1; ++i) {
		grid[i].col = i; grid[i].left = i - 1; grid[i].right = i + 1;
		grid[i].up = i; grid[i].down = i; cnt[i] = 0;
	}
	grid[1].left = m + 1; grid[m + 1].right = 1;
}
inline void remove(int x) {
	grid[grid[x].right].left = grid[x].left;
	grid[grid[x].left].right = grid[x].right;
	for (int y = grid[x].down; y != x; y = grid[y].down)
		for (int z = grid[y].right; z != y; z = grid[z].right) {
			cnt[grid[z].col]--;
			grid[grid[z].down].up = grid[z].up;
			grid[grid[z].up].down = grid[z].down;
		}
}
inline void resume(int x) {
	for (int y = grid[x].up; y != x; y = grid[y].up)
		for (int z = grid[y].left; z != y; z = grid[z].left) {
			cnt[grid[z].col]++;
			grid[grid[z].up].down = z;
			grid[grid[z].down].up = z;
		}
	grid[grid[x].right].left = x; grid[grid[x].left].right = x;
}
inline void add(int x, int y) {
	tot++; cnt[y]++;
	if (!head[x]) head[x] = tot;
	if (!tail[x]) tail[x] = tot;
	grid[tot].row = x; grid[tot].col = y;
	grid[tot].up = grid[y].up; grid[grid[y].up].down = tot;
	grid[tot].down = y; grid[y].up = tot;
	grid[tot].left = tail[x]; grid[tail[x]].right = tot;
	grid[tot].right = head[x]; grid[head[x]].left = tot;
	tail[x] = tot;
}
inline bool dfs(int dep) {
	if (grid[m + 1].right == m + 1) return true;
	int x = grid[m + 1].right;
	for (int i = x; i != m + 1; i = grid[i].right) if (cnt[i] < cnt[x]) x = i;
	if (!cnt[x]) return false;
	remove(x);
	for (int i = grid[x].down; i != x; i = grid[i].down) {
		for (int j = grid[i].right; j != i; j = grid[j].right) remove(grid[j].col);
		if (dfs(dep + 1)) return true;
		for (int j = grid[i].left; j != i; j = grid[j].left) resume(grid[j].col);
	}
	resume(x); return false;
}
inline void clear() { for (int i = 1; i <= tot; ++i) grid[i].clear(); }
