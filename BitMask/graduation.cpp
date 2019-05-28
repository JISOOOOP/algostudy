#include <iostream>
#include <vector>

using namespace std;

// subject[i] = i과목의 선이수 과목
// semester[i] = i학기 중 들을 수 있는 과목
vector<int> subject, semester;

int bitCount(int bit)		// 1 bit 갯수 세기

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

	// 이번 학기에 들을 수 있는 과목
	// 개설 과목 & 선이수과목 수강 과목
	int canTake = 0;


}

int bitCount(int bit) {
	if (bit == 0) return 0;
	return (bit % 2) + bitCount(bit / 2);
}