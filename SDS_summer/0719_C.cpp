#include <iostream>
#include <vector>

using namespace std;

vector<bool> check;

int findPrime(int N);

int main() {
	// input
	int N, K;
	cin >> N >> K;
	check = vector<bool>(N + 1, false);

	// proc
	int ret = 0;
	int cnt = 0;
	int idx = 0;
	while((idx = findPrime(N)) != -1){
		++cnt;
		if (cnt == K) {
			ret = idx;
			break;
		}
		for (int i = idx * 2; i <= N; i += idx) {
			if (!check[i]) {
				check[i] = true;
				++cnt;
				if (cnt == K) {
					ret = i;
					break;
				}
			}
		}
	}

	cout << ret << endl;
}

int findPrime(int N) {
	for (int i = 2; i <= N; ++i) {
		if (!check[i]) {
			check[i] = true;
			return i;
		}
	}
	return -1;
}