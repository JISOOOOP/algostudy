#include <iostream>

using namespace std;

int arr[1100][1100];
int dp[1100][1100];

int calcPartialSum(int s1, int s2, int e1, int e2);

int main() {
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &arr[i][j]);
		}
	}

	// init
	dp[1][1] = arr[1][1];
	for (int i = 2; i <= N; ++i) {
		dp[1][i] = dp[1][i - 1] + arr[1][i];
		dp[i][1] = dp[i - 1][1] + arr[i][1];
	}

	for (int i = 2; i <= N; ++i) {
		for (int j = 2; j <= N; ++j) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
		}
	}

	for (int i = 0; i < M; ++i) {
		int s1, s2, e1, e2;
		scanf("%d %d %d %d", &s1, &s2, &e1, &e2);
		printf("%d\n", calcPartialSum(s1, s2, e1, e2));
	}
}

int calcPartialSum(int s1, int s2, int e1, int e2) {
	if (s1 == e1 && s2 == e2) return arr[s1][s2];
	int ret = dp[e1][e2];
	int cnt = 0;
	if (s1 > 1) {
		ret -= dp[s1 - 1][e2];
		++cnt;
	}
	if (s2 > 1) {
		ret -= dp[e1][s2 - 1];
		++cnt;
	}
	if (cnt == 2) ret += dp[s1 - 1][s2 - 1];
	return ret;
}