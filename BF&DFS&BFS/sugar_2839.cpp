#include <iostream>
#include <vector>

using namespace std;

vector<int> cache(5001, -1);

int sugar(int N);
int min(int a, int b);

int main() {

	int N;
	cin >> N;

	int result = sugar(N);
	if (result > 2000) cout << -1 << endl;
	else cout << result << endl;
}

int sugar(int N) {
	// base case
	if (N < 0) return 2000;
	if (N == 0) return 0;

	// memoization
	int& ret = cache[N];
	if (ret != -1) return ret;

	return ret = min(1 + sugar(N - 3), 1 + sugar(N - 5));
}

int min(int a, int b) {
	return a > b ? b : a;
}