#include <iostream>
#include <vector>

using namespace std;

// subject[i] = i������ ���̼� ����
// semester[i] = i�б� �� ���� �� �ִ� ����
vector<int> subject, semester;

int bitCount(int bit)		// 1 bit ���� ����

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N, K, M, L;
		cin >> N >> K >> M >> L;

		// input subject
		for (int n = 0; n < N; ++n) {
			subject.push_back(0);
			int Ri;
			cin >> Ri;
			for (int ri = 0; ri < Ri; ++ri) {
				int shift;
				cin >> shift;
				subject[n] |= (1 << shift);
			}
		}

		// input semester
		for (int m = 0; m < M; ++m) {
			semester.push_back(0);
			int Si;
			cin >> Si;
			for (int si = 0; si < Si; ++si) {
				int shift;
				cin >> shift;
				semester[m] |= (1 << shift);
			}
		}
		
		// proc
		
	}
}

int graduation(int semesterNum, int taken, int K) {
	// base case
	if (bitCount(taken) >= K) return 0;

	// �̹� �б⿡ ���� �� �ִ� ����
	// ���� ���� & ���̼����� ���� ����
	int canTake = 0;


}

int bitCount(int bit) {
	if (bit == 0) return 0;
	return (bit % 2) + bitCount(bit / 2);
}