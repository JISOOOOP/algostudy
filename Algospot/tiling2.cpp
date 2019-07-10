#include <iostream>
#include <vector>

#define MOD		1000000007

using namespace std;

vector<int> cache, result;

int tiling2(int n);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		
		// input && init && alloc
		int N;
		scanf("%d", &N);

		for (int i = 0; i <= N; ++i) {
			cache.push_back(0);
		}

		// proc
		result.push_back(tiling2(N));

		// cache free
		cache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int tiling2(int n) {
	// base case
	if (n == 0) return 1;
	if (n < 0) return 0;

	// memoization
	int& ret = cache[n];
	if (ret) return ret;

	return ret = (tiling2(n - 1) + tiling2(n - 2)) % MOD;
}