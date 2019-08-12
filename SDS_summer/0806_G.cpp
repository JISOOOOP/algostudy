#include <iostream>
#include <memory.h>
#include <vector>
#include <math.h>

using namespace std;

int dp[1000001];
int p[1000001];

vector<int> idxTree;

int main() {
	int N;
	cin >> N;

	int i = 0;
	while (pow(2, i++) >= N);
	idxTree = vector<int>(pow(2, i) * 2, 0);

	int startIdx = pow(2, i);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &idxTree[startIdx + i]);
	}

	// init
	dp[1] = 1;
	memset(p, -1, sizeof(p));
	for (int i = 2; i <= N; ++i) {

	}
}