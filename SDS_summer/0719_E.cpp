#include <iostream>
#include <vector>

using namespace std;

vector<int> prime(1000000, 0);
vector<bool> check(4000002, true);

int primeCheck();

int main() {
	int prime_cnt = primeCheck();

	// input
	int N;
	cin >> N;

	// proc
	int s = 0, e = 0;
	int sum = prime[s];
	int ret = 0;
	while (e <= prime_cnt) {
		if (sum == N) {
			++ret;
			sum += prime[++e];
		}
		else if (sum < N) {
			sum += prime[++e];
		}
		else if (sum > N) {
			sum -= prime[s++];
		}
	}

	printf("%d\n", ret);
}

int primeCheck() {
	int prime_cnt = 0;
	for (int i = 2; i <= 4000000; ++i) {
		if (check[i]) {
			prime[prime_cnt++] = i;
			for (int j = i * 2; j <= 4000000; j += i) {
				check[j] = false;
			}
		}
	}
	return prime_cnt;
}