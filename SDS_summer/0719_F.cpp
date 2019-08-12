#include <iostream>
#include <vector>

using namespace std;

vector<bool> check(10000001, true);
vector<int> prime(10000000, 0);

int calcPrime();

int main() {
	// input
	int N;
	cin >> N;

	int prime_cnt = calcPrime();
	for (int i = 0; i < prime_cnt; ++i) {
		if (N == 1) break;
		while (N % prime[i] == 0) {
			N /= prime[i];
			printf("%d\n", prime[i]);
		}
	}
}

int calcPrime() {
	int prime_cnt = 0;
	for (int i = 2; i <= 10000000; ++i) {
		if (check[i]) {
			prime[prime_cnt++] = i;
			for (int j = 2; j * i <= 10000000; ++j) {
				check[j * i] = false;
			}
		}
	}
	return prime_cnt;
}