#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> josephus(queue<int>& roman, int K);
vector< vector<int> > result;

int main() {
	
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N, K;
		cin >> N >> K;

		queue<int> roman;
		for (int n = 1; n <= N; ++n) {
			roman.push(n);
		}
		
		vector<int> alive = josephus(roman, K);
		result.push_back(alive);
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		for (int j = 0; j < result[i].size(); ++j) {
			cout << result[i][j] << ' ';
		}
		cout << endl;
	}

	// result free
	result.clear();
}

vector<int> josephus(queue<int>& roman, int K) {

	int killed = 0;

	roman.pop();
	++killed;

	while (roman.size() > 2) {
		for (int k = 1; k < K; ++k) {
			int skip = roman.front();
			roman.pop();
			roman.push(skip);
		}
		roman.pop();
		++killed;
	}

	vector<int> alive;
	for (int i = 0; i < 2; ++i) {
		int front = roman.front();
		roman.pop();
		alive.push_back(front);
	}
	sort(alive.begin(), alive.end());

	return alive;
}