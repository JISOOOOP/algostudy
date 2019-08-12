#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<bool> check(1000001, true);
vector<int> prime(1000000, 0);

int calcPrime();

int main() {
	// input
	string P;
	int K;
	cin >> P;
	cin >> K;

	int prime_cnt = calcPrime();

	// proc
	int ret = -1;
	for (int i = 0; i < prime_cnt; ++i) {
		ret = 0;
		for (int j = 0; j < P.length(); ++j) {
			int n = P[j] - '0';
			ret = ret * 10 + (n % prime[i]);
		}
		if (ret == 0) {
			ret = i;
			break;
		}
	}

	if (ret == -1) cout << "GOOD" << endl;
	else cout << "BAD " << prime[ret] << endl;
}

int calcPrime() {
	int prime_cnt = 0;
	for (int i = 2; i <= 1000000; ++i) {
		if (check[i]) {
			prime[prime_cnt++] = i;
			for (int j = 2; j * i <= 1000000; ++j) {
				check[i * j] = false;
			}
		}
	}
	return prime_cnt;
}