#include <iostream>

using namespace std;

int arr[100001];
int dp[100001];

int main() {
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}

	dp[0] = arr[0];
	for (int i = 1; i < N; ++i) {
		dp[i] = dp[i - 1] + arr[i];
	}

	for (int i = 0; i < M; ++i) {
		int s, e;
		scanf("%d %d", &s, &e);
		printf("%d\n", dp[e - 1] - dp[s - 1] + arr[s - 1]);
	}
}