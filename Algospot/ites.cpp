#include <iostream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

vector<int> result;

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int K, N;
		cin >> K >> N;

		// proc
		int ret = 0;

		queue<int> partialSum;

		long long a = 1983;
		long long signal = a % 10000 + 1;

		partialSum.push(signal);
		int sum = signal;

		for (int i = 1; i < N; ++i) {
			a = a * 214013 + 2531011;
			a %= (long long)1 << 32;
			signal = a % 10000 + 1;

			// queue 원소의 합이 K보다 큰경우 작아질때 까지 pop
			while (sum > K) {
				int temp = partialSum.front();
				partialSum.pop();
				sum -= temp;
			}

			// sum == K 이면 ++ret
			if (sum == K) ++ret;

			partialSum.push(signal);
			sum += signal;
		}
		result.push_back(ret);
	}
	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();

}