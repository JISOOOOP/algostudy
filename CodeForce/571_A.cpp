#include <iostream>

using namespace std;

int main() {
	// input
	int N, M, K;
	cin >> N >> M >> K;

	if (N <= M && N <= K) {
		cout << "Yes" << endl;
		return 0;
	}

	cout << "No" << endl;
}