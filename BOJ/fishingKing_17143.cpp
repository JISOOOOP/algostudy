#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct fish {
	int r;
	int c;
	int v;
	int d;
	int s;
	fish(int _r, int _c, int _v, int _d, int _s) {
		r = _r;
		c = _c;
		v = _v;
		d = _d;
		s = _s;
	}
	fish() {}
};

// up down left right
const int dr[5] = { 0, -1, 1, 0, 0 };
const int dc[5] = { 0, 0, 0, 1, -1 };

vector< vector<bool> > visited;
vector<fish> aqua;

int fishingKing();
vector<fish> movefish(queue<fish>& q);
void v2q(vector<fish>& v, queue<fish>& q, int size);
int throwArrow(vector<fish> &cur, int size, int c);
int find_r_c(vector<fish> &cur, int size, int r, int c);
void fishPosCheck(vector<fish> &cur, int size);
void memsetZero_visited();

int main() {
	// input
	int R, C, M;
	cin >> R >> C >> M;

	visited = vector< vector<bool> >(R, vector<bool>(C, false));
	aqua = vector<fish>(M);
	for (int i = 0; i < M; ++i) {
		int r, c, v, d, s;
		cin >> r >> c >> v >> d >> s;
		aqua[i] = fish(r - 1, c - 1, v, d, s);
	}

	// proc
	cout << fishingKing();

	// free
	visited.clear();
	aqua.clear();
}

int fishingKing() {
	int ret = 0;
	// init
	vector<fish> cur(aqua.size());
	for (int i = 0; i < aqua.size(); ++i) {
		cur[i] = aqua[i];
	}
	fishPosCheck(cur, cur.size());

	for (int c = 0; c < visited[0].size(); ++c) {
		ret += throwArrow(cur, cur.size(), c);
		memsetZero_visited();

		queue<fish> q;
		v2q(cur, q, cur.size());
		vector<fish> temp = movefish(q);
		cur.clear();
		cur = vector<fish>(temp.size());
		for (int i = 0; i < cur.size(); ++i) {
			cur[i] = temp[i];
		}
	}
	return ret;
}

vector<fish> movefish(queue<fish>& q) {
	vector<fish> ret;

	while (!q.empty()) {
		fish cur = q.front();
		q.pop();
		if (cur.r == -1) continue;

		for (int i = 0; i < cur.v; ++i) {
			cur.r += dr[cur.d];
			cur.c += dc[cur.d];
			// outOfRange
			if (cur.r < 0 || cur.r >= visited.size() || cur.c < 0 || cur.c >= visited[0].size()) {
				// convert direction
				if (cur.d == 1) cur.d = 2;
				else if (cur.d == 2) cur.d = 1;
				else if (cur.d == 3) cur.d = 4;
				else if (cur.d == 4) cur.d = 3;
				
				cur.r += (dr[cur.d] * 2);
				cur.c += (dc[cur.d] * 2);
			}
		}
		// collision
		if (visited[cur.r][cur.c]) {
			int idx = find_r_c(ret, ret.size(), cur.r, cur.c);
			if (ret[idx].s < cur.s) {
				ret[idx].v = cur.v;
				ret[idx].d = cur.d;
				ret[idx].s = cur.s;
			}
		}
		else {
			visited[cur.r][cur.c] = true;
			ret.push_back(cur);
		}
	}
	return ret;
}

void v2q(vector<fish>& v, queue<fish>& q, int size) {
	for (int i = 0; i < size; ++i) {
		q.push(v[i]);
	}
}

int throwArrow(vector<fish> &cur, int size, int c) {
	for (int r = 0; r < visited.size(); ++r) {
		if (visited[r][c]) {
			int idx = find_r_c(cur, size, r, c);
			cur[idx].r = -1;
			return cur[idx].s;
		}
	}
	return 0;
}

int find_r_c(vector<fish> &cur, int size, int r, int c) {
	for (int i = 0; i < size; ++i) {
		if (cur[i].r == r && cur[i].c == c) {
			return i;
		}
	}
	cout << "find_r_c Error" << endl;
}

void fishPosCheck(vector<fish> &cur, int size) {
	for (int i = 0; i < size; ++i) {
		visited[cur[i].r][cur[i].c] = true;
	}
}

void memsetZero_visited() {
	for (int i = 0; i < visited.size(); ++i) {
		for (int j = 0; j < visited[0].size(); ++j) {
			visited[i][j] = 0;
		}
	}
}