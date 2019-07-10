#include <iostream>
#include <vector>

using namespace std;

int proc(vector<int>& seq);
vector<int> calcRNumSum(vector<int>& seq);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;

		vector<int> seq(1000001, 0);
		for (int i = 0; i < N; ++i) {
			int temp;
			cin >> temp;
			++seq[temp];
		}

		// proc
		cout << "#" << t + 1 << " " << proc(seq) << endl;

		// free
		seq.clear();
	}
}

int proc(vector<int>& seq) {
	vector<int> RnumSum = calcRNumSum(seq);
	for (int i = 1000000; i >= 0; --i) {
		if (RnumSum[i] >= i) return i;
	}
}

vector<int> calcRNumSum(vector<int>& seq) {
	vector<int> RnumSum(1000001, 0);
	RnumSum[1000000] = seq[1000000];
	for (int i = 999999; i >= 0; --i) {
		RnumSum[i] = RnumSum[i + 1] + seq[i];
	}
	return RnumSum;
}