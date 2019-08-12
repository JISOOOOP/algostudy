#include <iostream>
#include <string>

using namespace std;

bool board[1001][1001];
int dp[1001][1001];

int min(int a, int b) { return a < b ? a : b; }

int main() {
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		string str;
		cin >> str;
		for (int j = 0; j < M; ++j) {
			board[i][j] = str[j] - '0';
		}
	}

	// init
	for (int i = 0; i < N; ++i) {
		if (board[i][0]) dp[i][0] = 1;
	}
	for (int i = 0; i < M; ++i) {
		if (board[0][i]) dp[0][i] = 1;
	}

	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < M; ++j) {
			if (!board[i][j]) dp[i][j] = 0;
			else {
				dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j])) + 1;
			}
		}
	}

	int ret = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (ret < dp[i][j]) ret = dp[i][j];
		}
	}
	cout << ret * ret << endl;
}