#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;

const int num[4] = { 0, 1, 2, 5 };

int calcDivNum(int X);
int calcDigit(int n);
void dfs(int dig, int curNum, int X, int& ret);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int X;
		cin >> X;

		//proc
		cout << "#" << t + 1 << " " << calcDivNum(X) << endl;
	}
}

int calcDivNum(int X) {
	int ret = 0;
	int digit = calcDigit(X);
	
	dfs(digit, 0, X, ret);
	return ret;
}

void dfs (int dig, int curNum, int X, int& ret) {
	// base case
	if (dig == 0) {
		if (curNum > X) return;
		if (curNum == 0) return;
		ll upbound = pow(10, calcDigit(curNum));
		if (upbound % curNum == 0) ++ret;
		return;
	}

	for (int i = 0; i < 4; ++i) {
		dfs(dig - 1, curNum * 10 + num[i], X, ret);
	}
}

int calcDigit(int n) {
	int ret = 0;
	while (n != 0) {
		n /= 10;
		++ret;
	}
	return ret;
}