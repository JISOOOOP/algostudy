#include <iostream>
#include <vector>

using namespace std;

struct pos {
	int r;
	int c;
	pos(int _r, int _c) :r(_r), c(_c) {}
	pos() {}
};

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

vector< vector<int> > tourMap;
vector<bool> visited;

int sujiTrip();
int calcFoodNum();
void dfs(pos cur, int maxTake, int taken, int& ret, int& exitFlag);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int R, C;
		cin >> R >> C;

		tourMap = vector< vector<int> >(R, vector<int>(C, 0));
		visited = vector<bool>(26, 0);
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				char temp;
				cin >> temp;
				tourMap[i][j] = temp - 65;
			}
		}

		// proc
		cout << "#" << t + 1 << " " << sujiTrip() << endl;

		// free
		tourMap.clear();
		visited.clear();
	}
}

int sujiTrip() {
	int maxTake = calcFoodNum();
	int ret = 0, exitFlag = 0;
	dfs(pos(0, 0), maxTake, 0, ret, exitFlag);
	return ret;
}

int calcFoodNum() {
	int ret = 0;
	for (int i = 0; i < tourMap.size(); ++i) {
		for (int j = 0; j < tourMap[0].size(); ++j) {
			if (!visited[tourMap[i][j]]) {
				++ret;
				visited[tourMap[i][j]] = true;
			}
		}
	}
	for (int i = 0; i < visited.size(); ++i) visited[i] = false;
	return ret;
}

void dfs(pos cur, int maxTake, int taken, int& ret, int& exitFlag) {
	int flag = 0;
	// backTracking
	visited[tourMap[cur.r][cur.c]] = true;
	++taken;
	for (int i = 0; i < 4; ++i) {
		int next_r = cur.r + dr[i];
		int next_c = cur.c + dc[i];
		// outOfRange
		if (next_r < 0 || next_r >= tourMap.size() || next_c < 0 || next_c >= tourMap[0].size()) continue;
		// taken
		if (visited[tourMap[next_r][next_c]]) continue;

		flag = 1;
		dfs(pos(next_r, next_c), maxTake, taken, ret, exitFlag);
		if (exitFlag == 1) return;
	}
	visited[tourMap[cur.r][cur.c]] = false;

	if (flag == 0) {
		if (ret < taken) ret = taken;
		if (ret == maxTake) exitFlag = 1;
	}
}