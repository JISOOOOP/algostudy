#include <iostream>
#include <vector>

using namespace std;

struct info {
	int a, b;
	info(int _a, int _b) : a(_a), b(_b) {}
};

vector< vector<bool> > cmp;
vector<info> _cmp;

bool canOrder(int idx);

int main() {
	// input
	int N, M;
	cin >> N >> M;

	cmp = vector< vector<bool> >(N + 1, vector<bool>(N + 1, false));
	for (int i = 0; i < M; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		cmp[a][b] = true;
		_cmp.push_back(info(a, b));
	}

	// proc
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (cmp[i][k] && cmp[k][j]) {
					cmp[i][j] = true;
				}
			}
		}
	}

	for (int i = 1; i < cmp.size(); ++i) {
		for (int j = 1; j < cmp.size(); ++j) {
			if (cmp[i][j]) cmp[j][i] = true;
		}
	}
	

	int ret = 0;
	for (int i = 1; i <= N; ++i) {
		if (canOrder(i)) ++ret;
	}

	printf("%d\n", ret);

	// free
	cmp.clear();
}

bool canOrder(int idx) {
	for (int i = 1; i < cmp.size(); ++i) {
		if (i == idx) continue;
		if (!cmp[i][idx]) return false;
	}

	for (int i = 1; i < cmp.size(); ++i) {
		if (i == idx) continue;
		if (!cmp[idx][i]) return false;
	}
	return true;
}