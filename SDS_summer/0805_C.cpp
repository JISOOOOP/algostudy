#include <iostream>
#include <memory.h>

using namespace std;

int cache[31][31];

int proc(int n, int m);

int main() {
	int T;
	cin >> T;

	memset(cache, -1, sizeof(cache));
	for (int t = 0; t < T; ++t) {
		int N, M;
		cin >> N >> M;

		for (int i = 0; i < 31; ++i) {
			cache[i][i] = 1;
			cache[0][i] = 0;
		}
		cout << proc(N, M) << endl;
	}
}

int proc(int n, int m) {
	// base case
	if (n == 1) return m;
	if (n > m) return 0;

	// memoization
	int& ret = cache[n][m];
	if (ret != -1) return ret;

	ret = 0;

	for (int i = 1; i <= m; ++i) {
		ret += proc(n - 1, m - i);
	}

	return ret;
}