#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
	pos() {}
};

// up right down left
const int pipe[8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 0, 1, 0},
	{0, 1, 0, 1},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1}
};

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

vector< vector<int> > sub;
vector< vector<bool> > visited;

int catchPrisoner(int R, int C, int L);
int calcVisited();
void v2q(vector<pos>& v, queue<pos>& q, int size);

int main() {
	//input
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, M, R, C, L;
		cin >> N >> M >> R >> C >> L;

		sub = vector< vector<int> >(N, vector<int>(M, 0));
		visited = vector< vector<bool> >(N, vector<bool>(M, false));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cin >> sub[i][j];
			}
		}

		// proc
		result[t] = catchPrisoner(R, C, L);

		// free
		sub.clear();
		visited.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int catchPrisoner(int R, int C, int L) {
	pos hole(R, C);
	queue<pos> q;
	q.push(hole);
	visited[R][C] = true;

	for (int l = 1; l < L; ++l) {
		vector<pos> temp;
		while (!q.empty()) {
			pos cur = q.front();
			q.pop();

			int curPipe = sub[cur.r][cur.c];
			for (int d = 0; d < 4; ++d) {
				if (pipe[curPipe][d]) {
					int next_r = cur.r + dr[d];
					int next_c = cur.c + dc[d];
					// outOfRange
					if (next_r < 0 || next_r >= sub.size() || next_c < 0 || next_c >= sub[0].size()) continue;
					// visited
					if (visited[next_r][next_c]) continue;

					int nextPipe = sub[next_r][next_c];
					if (pipe[nextPipe][(d + 2) % 4]) {
						visited[next_r][next_c] = true;
						temp.push_back(pos(next_r, next_c));
					}
				}
			}
		}
		v2q(temp, q, temp.size());
	}
	return calcVisited();
}

int calcVisited() {
	int ret = 0;
	for (int i = 0; i < visited.size(); ++i) {
		for (int j = 0; j < visited[0].size(); ++j) {
			if (visited[i][j]) ++ret;
		}
	}
	return ret;
}

void v2q(vector<pos>& v, queue<pos>& q, int size) {
	for (int i = 0; i < size; ++i) {
		q.push(v[i]);
	}
}