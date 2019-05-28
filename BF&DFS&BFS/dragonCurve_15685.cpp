#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct start {
	int r;
	int c;
	int d;
	int g;
	start(int _r, int _c, int _d, int _g) {
		r = _r;
		c = _c;
		d = _d;
		g = _g;
	}
	start() {}
};

// right up left down
const int dr[4] = { 0, -1, 0, 1 };
const int dc[4] = { 1, 0, -1, 0 };

vector<start> point;
vector< vector<bool> > visited(101, vector<bool>(101, false));

int dragonCurve();
int calcSquare();
void pathVisit(vector<int>& path, start point, int size);
vector<int> makePath(start point);
void v2s(vector<int>& v, stack<int>& s, int size);

int main() {
	// input
	int N;
	cin >> N;

	point = vector<start>(N);
	for (int i = 0; i < N; ++i) {
		int r, c, d, g;
		cin >> c >> r >> d >> g;
		point[i] = start(r, c, d, g);
	}

	// proc
	cout << dragonCurve();

	// free
	point.clear();
	visited.clear();
}

int dragonCurve() {
	for (int i = 0; i < point.size(); ++i) {
		start cur = point[i];
		vector<int> path = makePath(cur);
		pathVisit(path, cur, path.size());
	}
	return calcSquare();
}

int calcSquare() {
	int ret = 0;
	for (int i = 0; i < visited.size(); ++i) {
		for (int j = 0; j < visited[0].size(); ++j) {
			if (visited[i][j]) {
				int next_r = i;
				int next_c = j;
				// right 0
				next_r += dr[0];
				next_c += dc[0];
				// outOfRange
				if (next_r < 0 || next_r >= visited.size() || next_c < 0 || next_c >= visited[0].size()) continue;
				if (visited[next_r][next_c]) {
					// down 3
					next_r += dr[3];
					next_c += dc[3];
					// outOfRange
					if (next_r < 0 || next_r >= visited.size() || next_c < 0 || next_c >= visited[0].size()) continue;
					if (visited[next_r][next_c]) {
						// left 2
						next_r += dr[2];
						next_c += dc[2];
						// outOfRange
						if (next_r < 0 || next_r >= visited.size() || next_c < 0 || next_c >= visited[0].size()) continue;
						if (visited[next_r][next_c]) ++ret;
					}
				}
			}
		}
	}
	return ret;
}

void pathVisit(vector<int>& path, start p, int size) {
	visited[p.r][p.c] = true;
	for (int i = 0; i < size; ++i) {
		int dir = path[i];
		p.r += dr[dir];
		p.c += dc[dir];
		visited[p.r][p.c] = true;
	}
}

vector<int> makePath(start point) {
	// init
	vector<int> path;
	path.push_back(point.d);

	stack<int> s;
	for (int g = 0; g < point.g; ++g) {
		v2s(path, s, path.size());
		while (!s.empty()) {
			int dir = s.top();
			s.pop();

			int nextDir = (dir + 1) % 4;
			path.push_back(nextDir);
		}
	}
	return path;
}

void v2s(vector<int>& v, stack<int>& s, int size) {
	for (int i = 0; i < size; ++i) {
		s.push(v[i]);
	}
}
//
//// debug
//void printVisit() {
//	for (int i = 0; i < 20; ++i) {
//		for (int j = 0; j < 20; ++j) {
//			printf("%3d", visited[i][j]? 1 : 0);
//		}
//		printf("\n");
//	}
//}
//
//void printPath(vector<int>& p, int size) {
//	for (int i = 0; i < size; ++i) {
//		printf("%3d", p[i]);
//	}
//	cout << endl;
//}