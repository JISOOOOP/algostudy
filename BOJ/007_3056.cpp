#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector< vector<double> > success;
vector<double> cache;

double calcProb(int jimi, int taken_job);

int main() {
	// input && init && alloc
	int N;
	cin >> N;

	for (int n = 0; n <= N; ++n) {
		vector<double> ele(N + 1, 0);
		success.push_back(ele);
	}

	int cacheSize = pow(2, N);
	for (int i = 0; i < cacheSize; ++i) cache.push_back(-1);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int temp;
			cin >> temp;
			success[i][j] = (double)temp / 100;
		}
	}

	// proc
	cout << fixed;
	cout.precision(6);
	cout << (double)calcProb(0, 0) * 100;
}

double calcProb(int jimi, int taken_job) {
	// base case
	if (jimi == success.size() - 1) return 1.0;

	// memoization
	double& ret = cache[taken_job];
	if (ret != -1) return ret;

	ret = 0;

	for (int i = 0; i < success.size() - 1; ++i) {
		// 이미 수행한 job이면 pass
		if (taken_job & (1 << i)) continue;
		double temp = success[jimi][i] * calcProb(jimi + 1, taken_job | (1 << i));
		if (temp > ret) ret = temp;
	}

	return ret;
}