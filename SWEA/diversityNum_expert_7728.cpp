#include <iostream>
#include <vector>

using namespace std;

vector<bool> isUsed;

int diversityNum(int X);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		long long X;
		cin >> X;

		isUsed = vector<bool>(10, false);

		// proc
		cout << "#" << t + 1 << " " << diversityNum(X) << endl;

		// free
		isUsed.clear();
	}
}

int diversityNum(int X) {
	int ret = 0;

	for (int i = X; i > 0; i /= 10) {
		isUsed[i % 10] = true;
	}

	for (int i = 0; i < 10; ++i) {
		if (isUsed[i]) ++ret;
	}
	return ret;
}