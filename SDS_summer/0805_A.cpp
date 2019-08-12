#include <iostream>
#include <memory.h>

using namespace std;

int cache[11][11];

int proc(int n, int k);

int main() {
	int N, K;
	cin >> N >> K;

	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < 11; ++i) {
		cache[i][0] = 1;
		cache[i][1] = i;
	}
	cout << proc(N, K) << endl;

	return 0;
}

int proc(int n, int k) {
	// base case
	if (k == 1) return n;
	if (n == k) return 1;

	int& ret = cache[n][k];
	if (ret != -1) return ret;

	return ret = proc(n - 1, k - 1) + proc(n - 1, k);
}