#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

struct pos {
	int r;
	int c;
	pos(int _r, int _c) : r(_r), c(_c) {}
	pos() {}
};

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

vector< vector<int> > board(4, vector<int>(4, 0));
bool visited[10000000] = { false, };

int proc();
void dfs(int takeNum, int curNum, pos p, int& ret);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				cin >> board[i][j];
			}
		}

		// proc
		cout << "#" << t + 1 << " " << proc() << endl;

		// free
		memset(visited, false, sizeof(visited));
	}
}

int proc() {
	int ret = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			dfs(0, 0, pos(i, j), ret);
		}
	}
	return ret;
}

void dfs(int takeNum, int curNum, pos p, int& ret) {
	// base case
	if (takeNum == 7) {
		if (visited[curNum]) return;
		++ret;
		visited[curNum] = true;
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int next_r = p.r + dr[i];
		int next_c = p.c + dc[i];
		// outOfRange
		if (next_r < 0 || next_r > 3 || next_c < 0 || next_c > 3) continue;

		dfs(takeNum + 1, curNum * 10 + board[p.r][p.c], pos(next_r, next_c), ret);
	}
}