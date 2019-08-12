#include <iostream>
#include <memory.h>
#include <math.h>
#include <vector>

#define MAX_N	17
#define INF		987654321

using namespace std;

vector< vector<int> >dp;
int cost[MAX_N][MAX_N];

int min(int a, int b) { return a < b ? a : b; }

int proc(int state, int cur, int N);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &cost[i][j]);
		}
	}
	dp = vector< vector<int> >(70000, vector<int>(MAX_N, INF));

	cout << proc(1, 0, N) << endl;
}

int proc(int state, int cur, int N) {
	// base case
	if (state == (1 << N) - 1) {
		return cost[cur][0] == 0 ? INF : cost[cur][0];
	}

	int& ret = dp[state][cur];
	if (ret != INF) return ret;

	for (int i = 0; i < N; ++i) {
		if ((state & (1 << i)) == 0 && cost[cur][i] != 0) {
			dp[state][cur] = min(dp[state][cur], proc(state | (1<<i), i, N) + cost[cur][i]);
		}
	}

	return dp[state][cur];
}