#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> divisor;

int proc(int P);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int P;
		cin >> P;

		divisor = vector<int>(P, 0);
		for (int i = 0; i < P; ++i) {
			cin >> divisor[i];
		}

		// proc
		cout << "#" << t + 1 << " " << proc(P) << endl;

		// free
		divisor.clear();
	}
}

int proc(int P) {
	sort(divisor.begin(), divisor.end());
	if (P % 2 == 0) {
		return divisor[0] * divisor[divisor.size() - 1];
	}
	else {
		return divisor[P / 2] * divisor[P / 2];
	}
}