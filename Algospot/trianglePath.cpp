#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > tri, cache;
vector<int> result;

int max(int a, int b);
int triPath(int r, int c);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N;
		scanf("%d", &N);

		for (int n = 0; n < N; ++n) {
			vector<int> ele(N);
			vector<int> ele_c(N, -1);
			tri.push_back(ele);
			cache.push_back(ele_c);
		}

		for (int r = 0; r < N; ++r) {
			for (int c = 0; c <= r; ++c) {
				int temp;
				scanf("%d", &temp);
				tri[r][c] = temp;
			}
		}

		// proc
		result.push_back(triPath(0, 0));

		// free
		cache.clear();
		tri.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
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