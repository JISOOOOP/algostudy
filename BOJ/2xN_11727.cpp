#include <iostream>
#include <vector>

using namespace std;

vector<int> cache(1001, -1);

int tiling_2N(int N);

int main() {
	// input
	int N;
	cin >> N;

	// proc
	cache[1] = 1;
	cache[2] = 3;
	cout << tiling_2N(N);
}

int tiling_2N(int N) {
	int& ret = cache[N];
	if (ret != -1) return ret;

	ret = (tiling_2N(N - 1) + (2 * tiling_2N(N - 2))) % 10007;

	return ret;
}