#include <iostream>

#define MAX_N	101
#define MAX_M	10000000
#define MAX_COST	10001

using namespace std;

int mem[MAX_N];
int cost[MAX_N];
int dp[MAX_COST];

int max(int a, int b) { return a > b ? a : b; }

int main() {
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		scanf("%d", &mem[i]);
	}
	int sum = 0;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &cost[i]);
		sum += cost[i];
	}

	// init
	dp[0] = 0;
	dp[cost[1]] = mem[1];
	
	for (int i = 2; i <= N; ++i) {
		for (int j = sum; j >= cost[i]; --j) {
			dp[j] = max(dp[j], dp[j - cost[i]] + mem[i]);
		}
	}

	for (int i = 1; i <= sum; ++i) {
		if (dp[i] >= M) {
			cout << i << endl;
			return 0;
		}
	}
}