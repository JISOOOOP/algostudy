#include <iostream>

using namespace std;

int tri[501][501];
int dp[501][501];

int max(int a, int b) { return a > b ? a : b; }

int main() {
	int N;
	cin >> N;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= i; ++j) {
			scanf("%d", &tri[i][j]);
		}
	}

	for (int i = 1; i <= N; ++i) {
		dp[N][i] = tri[N][i];
	}

	for (int i = N - 1; i >= 1; --i) {
		for (int j = 1; j <= i; ++j) {
			dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + tri[i][j];
		}
	}

	cout << dp[1][1] << endl;
}