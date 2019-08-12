#include <iostream>

using namespace std;

int stair[301];
int dp[2][301];

int max(int a, int b) { return a > b ? a : b; }

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		scanf("%d", &stair[i]);
	}

	// init
	dp[0][0] = stair[0];
	dp[0][1] = stair[1];
	dp[1][1] = stair[0] + stair[1];

	for (int i = 2; i < N; ++i) {
		dp[0][i] = max(dp[0][i - 2], dp[1][i - 2]) + stair[i];
		dp[1][i] = dp[0][i - 1] + stair[i];
	}

	cout << max(dp[0][N - 1], dp[1][N - 1]) << endl;
}