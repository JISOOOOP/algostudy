#include <iostream>
#include <vector>
#include <memory.h>

typedef long long ll;

using namespace std;

ll cache[101][21];

vector<int> number;

int main() {
	int N;
	cin >> N;

	number = vector<int>(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> number[i];
	}

	memset(cache, 0, sizeof(cache));

	cache[0][number[0]] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < 21; ++j) {
			if (j + number[i] < 21) cache[i][j + number[i]] += cache[i - 1][j];
			if (j - number[i] >= 0) cache[i][j - number[i]] += cache[i - 1][j];
		}
	}
	cout << cache[N - 2][number[N - 1]] << endl;
}

// 다시보기
