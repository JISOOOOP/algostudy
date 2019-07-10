#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

struct pos {
	int r;
	int c;
	pos(int _r, int _c) : r(_r), c(_c) {}
	pos() {}
};

vector< vector<int> > cheese;
vector< vector<bool> > visited;
vector<bool> isThere;
vector< list<pos> > tastePos;

int thiefCheese();
void eatCheese(int n);
int calcCheeseGroup(int& exitFlag);
void bfs(pos start);
void memsetVisited();
pos findStart();
void checkThere();

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;
		cheese = vector< vector<int> >(N, vector<int>(N, 0));
		visited = vector< vector<bool> >(N, vector<bool>(N, false));
		isThere = vector<bool>(101, 0);
		tastePos = vector< list<pos> >(101);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> cheese[i][j];
			}
		}

		// proc
		cout << "#" << t + 1 << " " << thiefCheese() << endl;

		// free
		cheese.clear();
		visited.clear();
		isThere.clear();
		tastePos.clear();
	}
}

int thiefCheese() {
	int ret = 1;
	int exitFlag = 0;
	checkThere();
	for (int i = 1; i <= 100; ++i) {
		if (!isThere[i]) continue;
		exitFlag = 0;
		eatCheese(i);
		int temp = calcCheeseGroup(exitFlag);
		if (temp > ret) ret = temp;
		if (exitFlag == 0) break;
	}
	return ret;
}

void eatCheese(int n) {
	list<pos>::iterator it = tastePos[n].begin();
	while (it != tastePos[n].end()) {
		cheese[(*it).r][(*it).c] = 0;
		++it;
	}
}

int calcCheeseGroup(int& exitFlag) {
	int ret = 0;
	memsetVisited();
	pos cur = findStart();
	while (cur.r != -1) {
		exitFlag = 1;
		bfs(cur);
		++ret;
		cur = findStart();
	}
	return ret;
}

void bfs(pos start) {
	queue<pos> q;
	q.push(start);
	visited[start.r][start.c] = true;

	while (!q.empty()) {
		pos cur = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			int next_r = cur.r + dr[i];
			int next_c = cur.c + dc[i];
			// outOfRange
			if (next_r < 0 || next_r >= cheese.size() || next_c < 0 || next_c >= cheese.size()) continue;
			if (cheese[next_r][next_c] == 0 || visited[next_r][next_c]) continue;
			q.push(pos(next_r, next_c));
			visited[next_r][next_c] = true;
		}
	}
}

void memsetVisited() {
	for (int i = 0; i < visited.size(); ++i) {
		for (int j = 0; j < visited.size(); ++j) {
			visited[i][j] = false;
		}
	}
}

pos findStart() {
	for (int i = 0; i < cheese.size(); ++i) {
		for (int j = 0; j < cheese.size(); ++j) {
			if (cheese[i][j] > 0 && !visited[i][j]) return pos(i, j);
		}
	}
	return pos(-1, -1);
}

void checkThere() {
	for (int i = 0; i < cheese.size(); ++i) {
		for (int j = 0; j < cheese.size(); ++j) {
			isThere[cheese[i][j]] = true;
			tastePos[cheese[i][j]].push_back(pos(i, j));
		}
	}
}