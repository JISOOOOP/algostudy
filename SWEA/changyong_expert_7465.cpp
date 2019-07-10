#include <iostream>
#include <vector>

using namespace std;

vector< vector<bool> > group;
vector<bool> isGroup;

int changyong();
void dfs(int p);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N, M;
		cin >> N >> M;
		group = vector< vector<bool> >(N, vector<bool>(N, false));
		isGroup = vector<bool>(N, false);

		for (int i = 0; i < M; ++i) {
			int p1, p2;
			cin >> p1 >> p2;
			group[p1 - 1][p2 - 1] = group[p2 - 1][p1 - 1] = true;
		}

		// proc
		cout << "#" << t + 1 << " " << changyong() << endl;

		// free
		group.clear();
		isGroup.clear();
	}
}

int changyong() {
	int ret = 0;
	for (int i = 0; i < group.size(); ++i) {
		if (isGroup[i]) continue;
		dfs(i);
		++ret;
	}
	return ret;
}

void dfs(int p) {
	isGroup[p] = true;
	for (int i = 0; i < group.size(); ++i) {
		if (group[p][i] && !isGroup[i]) {
			dfs(i);
		}
	}
}