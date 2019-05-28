#include <iostream>
#include <vector>

using namespace std;

const int dr[4] = { 0, -1, 0, 1 };
const int dc[4] = { -1, 0, 1, 0 };

vector< vector<int> > forest, cache;

int greedyPanda();
int calcLife(int start_r, int start_c);

int main() {

	// input && init && alloc
	int N;
	cin >> N;

	for (int n = 0; n < N; ++n) {
		vector<int> ele(N, 0);
		vector<int> ele_c(N, 0);
		forest.push_back(ele);
		cache.push_back(ele_c);
	}

	for (int i = 0; i < forest.size(); ++i) {
		for (int j = 0; j < forest.size(); ++j) {
			cin >> forest[i][j];
		}
	}

	// proc
	cout << greedyPanda() << endl;
}

int greedyPanda() {
	int ret = 0;

	for (int i = 0; i < forest.size(); ++i) {
		for (int j = 0; j < forest.size(); ++j) {
			int temp = calcLife(i, j);
			if (temp > ret) ret = temp;
		}
	}
	return ret;
}

int calcLife(int start_r, int start_c) {
	// memoization
	int& ret = cache[start_r][start_c];
	if (ret) return ret;

	ret = 1;

	for (int i = 0; i < 4; ++i) {
		int next_r = start_r + dr[i];
		int next_c = start_c + dc[i];
		if (next_r >= 0 && next_r < forest.size() && next_c >= 0 && next_c < forest.size()) {		// outOfRange
			if (forest[start_r][start_c] < forest[next_r][next_c]) {								// 대나무 더 많은곳 찾으면
				int temp = 1 + calcLife(next_r, next_c);
				if (temp > ret) ret = temp;
			}
		}
	}

	return ret;
}