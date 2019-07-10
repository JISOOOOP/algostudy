#include <iostream>

using namespace std;

int calcRhombus(int n);

int main() {
	// input
	int N;
	cin >> N;

	// proc
	cout << calcRhombus(N);

	// free
}

int calcRhombus(int n) {
	// base case
	if (n == 1) return 1;

	return (n - 1) * 4 + calcRhombus(n - 1);
}