#include <iostream>
#include <vector>

#define MAX_N	1001

using namespace std;

int dp[MAX_N][MAX_N];

vector<int> score;

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;

		score = vector<int>(N + 2, 0);
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &score[i]);
		}

		// init
		for (int i = 1; i <= N; ++i) {
			if(N % 2 == 1) dp[i][i] = score[i];
			else dp[i][i] = 0;
		}

		for (int i = 1; i < N; ++i) {
			for (int j = 1; j + i <= N; ++j) {
				if (abs(N - (j + (j + i))) % 2 == 1) {
					dp[j][j + i] = max(dp[j + 1][j + i] + score[j], dp[j][j + i - 1] + score[j + i]);
				}
				else {
					dp[j][j + i] = min(dp[j + 1][j + i], dp[j][j + i - 1]);
				}
			}
		}

		cout << dp[1][N] << endl;

		// free
		score.clear();
	}
}