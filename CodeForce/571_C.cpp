#include <iostream>
#include <string>

using namespace std;

int main() {
	string As, Bs;
	cin >> As;
	cin >> Bs;

	// proc
	int A = As[0] % 2, B = Bs[0] % 2;
	for (int i = 1; i < As.size(); ++i) {
		A = A << 1;
		if (As[i] % 2 == 1) {
			A += 1;
		}
	}

	for (int i = 1; i < Bs.size(); ++i) {
		B = B << 1;
		if (Bs[i] % 2 == 1) {
			B += 1;
		}
	}

	int ret = 0;
	for (int i = 0; i <= As.size() - Bs.size(); ++i) {
		int temp = A >> (As.size() - Bs.size() - i);
		temp = temp & ((1 << Bs.size()) - 1);
		temp = temp ^ B;
		int cnt = 0;
		for (int j = 0; j < Bs.size(); ++j) {
			if ((temp >> j) % 2 == 1) ++cnt;
		}
		if (cnt % 2 == 0) ++ret;
	}


	cout << ret << endl;
}