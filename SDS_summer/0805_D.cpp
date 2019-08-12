#include <iostream>
#include <memory.h>

using namespace std;

typedef long long ll;

ll cache[201][201];

void proc(int n, int m, int k);
ll calcWordNum(int n, int m);
ll combi(int n, int k);

int main() {
	int N, M, K;
	cin >> N >> M >> K;

	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < 201; ++i) {
		cache[i][0] = 1;
	}

	if (calcWordNum(N, M) < K) {
		cout << "-1" << endl;
	}
	else {
		proc(N, M, K);
	}

	return 0;
}

void proc(int n, int m, int k) {
	// base case
	if (n == 0) {
		for (int i = 0; i < m; ++i) {
			cout << 'z';
		}
		return;
	}
	if (m == 0) {
		for (int i = 0; i < n; ++i) {
			cout << 'a';
		}
		return;
	}

	ll cur = calcWordNum(n - 1, m);
	if (k <= cur) {
		cout << 'a';
		proc(n - 1, m, k);
	}
	else {
		cout << 'z';
		proc(n, m - 1, k - cur);
	}
}

ll calcWordNum(int n, int m) {
	return combi(n + m, n);
}

ll combi(int n, int k) {
	// base case
	if (k == 1) return n;
	if (n == k) return 1;

	ll& ret = cache[n][k];
	if (ret != -1) return ret;

	ret = combi(n - 1, k - 1) + combi(n - 1, k);
	if (ret > 1000000000) ret = 1000000000;
	return ret;
}
