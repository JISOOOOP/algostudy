#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > tri, cache, cache_cnt;
vector<int> result;

int max(int a, int b);
int triPath(int r, int c);
int triPathCnt(int r, int c);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N;
		scanf("%d", &N);

		for (int n = 0; n <= N; ++n) {
			vector<int> ele(N + 1);
			vector<int> ele_c(N + 1, -1);
			vector<int> ele_cnt(N + 1, -1);
			tri.push_back(ele);
			cache.push_back(ele_c);
			cache_cnt.push_back(ele_cnt);
		}

		for (int r = 0; r < N; ++r) {
			for (int c = 0; c <= r; ++c) {
				int temp;
				scanf("%d", &temp);
				tri[r][c] = temp;
			}
		}

		// proc
		triPath(0, 0);
		result.push_back(triPathCnt(0, 0));

		// free
		cache.clear();
		cache_cnt.clear();
		tri.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int triPathCnt(int r, int c) {
	// base case
	if (r == tri.size() - 2) return 1;

	int& ret = cache_cnt[r][c];
	if (ret != -1) return ret;
	ret = 0;

	if (cache[r + 1][c] > cache[r + 1][c + 1]) return ret = triPathCnt(r + 1, c);
	if (cache[r + 1][c] < cache[r + 1][c + 1]) return ret = triPathCnt(r + 1, c + 1);
	if (cache[r + 1][c] == cache[r + 1][c + 1]) return ret = triPathCnt(r + 1, c) + triPathCnt(r + 1, c + 1);
}

int triPath(int r, int c) {
	// base case
	if (r == tri.size()) return 0;

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	return ret = tri[r][c] + max(triPath(r + 1, c), triPath(r + 1, c + 1));

}

int max(int a, int b) {
	return a > b ? a : b;
}