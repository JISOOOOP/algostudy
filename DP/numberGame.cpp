#include <iostream>
#include <vector>

using namespace std;

const int init = -9999;

vector<int> board, result;
vector< vector<int> > cache;

int numberGame(int start, int end);
int max(int a, int b);

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N;
		cin >> N;

		for (int n = 0; n < N; ++n) {
			int temp;
			cin >> temp;
			board.push_back(temp);
		}

		for (int n = 0; n < N; ++n) {
			vector<int> ele(N + 1, init);
			cache.push_back(ele);
		}

		// proc
		result.push_back(numberGame(0, board.size() - 1));

		// free
		board.clear();
		cache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int numberGame(int start, int end) {
	// base case
	if (start > end) return 0;

	// memoization
	int& ret = cache[start][end];
	if (ret != init) return ret;

	// 왼쪽꺼 하나 가져감
	ret = max(ret, board[start] - numberGame(start + 1, end));
	// 오른쪽꺼 하나 가져감
	ret = max(ret, board[end] - numberGame(start, end - 1));

	if (end - start + 1 >= 2) {		// 2개 이상일 때,
		// 왼쪽 두개 지움
		ret = max(ret, -1 * numberGame(start + 2, end));
		// 오른쪽 두개 지움
		ret = max(ret, -1 * numberGame(start, end - 2));
	}
	return ret;
}

int max(int a, int b) {
	return a > b ? a : b;
}