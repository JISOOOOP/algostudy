#include <iostream>

using namespace std;

struct Pair {
	int r;
	int c;
	int cnt;
	Pair(int _r, int _c, int _t) : r(_r), c(_c), cnt(_t) {}
	Pair() {}
};

Pair matrix[501];
Pair dp[501][501];

int min(int a, int b) { return a < b ? a : b; }

int main() {
	int N;
	cin >> N;

	for (int i = 1; i <= N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		matrix[i] = Pair(a, b, 0);
	}

	// init
	for (int i = 1; i <= N; ++i) {
		dp[N][i].cnt = 0;
		dp[N][i].r = matrix[i].r;
		dp[N][i].c = matrix[i].c;
	}

	for (int i = N - 1; i >= 1; --i) {
		for (int j = 1; j <= i; ++j) {
			int cnt1 = dp[i + 1][j].cnt + (dp[i + 1][j].r * dp[i + 1][j].c * dp[i + 1][j + 1].c);
			int cnt2 = dp[i + 1][j + 1].cnt + (dp[i + 1][j].r * dp[i + 1][j + 1].r * dp[i + 1][j + 1].c);
			dp[i][j].cnt = min(cnt1, cnt2);
			dp[i][j].r = dp[i + 1][j].r;
			dp[i][j].c = dp[i + 1][j + 1].c;
		}
	}

	//// debug
	//for (int i = 1; i <= N; ++i) {
	//	for (int j = 1; j <= N; ++j) {
	//		printf("%d ", dp[i][j].cnt);
	//	}
	//	cout << endl;
	//}

	cout << dp[1][1].cnt << endl;
}
