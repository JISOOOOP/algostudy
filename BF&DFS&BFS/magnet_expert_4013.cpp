#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct rotData {
	int idx;
	int dir;
	rotData(int i, int d) {
		idx = i;
		dir = d;
	}
};

vector< vector<int> >magnet;
vector<int> magnetIdx;

int magnetScore(int K, vector<rotData>& rot);
void rotation(int dir, int idx);
int calcScore();
//void printM();

int main() {

	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int K;
		cin >> K;

		magnet = vector< vector<int> >(4, vector<int>(8, 0));
		magnetIdx = vector<int>(4, 0);
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 8; ++j) {
				cin >> magnet[i][j];
			}
		}

		vector<rotData> rot;
		for (int k = 0; k < K; ++k) {
			int i, d;
			cin >> i >> d;
			rot.push_back(rotData(i - 1, d));
		}

		// proc
		result[t] = magnetScore(K, rot);

		/*printM();*/

		// free
		magnet.clear();
		magnetIdx.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();

}

int magnetScore(int K, vector<rotData>& rot) {
	for (int i = 0; i < K; ++i) {
		rotation(-rot[i].dir, rot[i].idx);
	}

	return calcScore();
}

// -1 = 시계, 1 = 반시계
void rotation(int dir, int idx) {
	vector<int> ret(4, 0);
	ret[idx] = dir;
	// 왼쪽 자석들
	for (int i = 0; idx - i > 0; ++i) {
		int connectA = (magnetIdx[idx - i] - 2 + 8) % 8;
		int connectB = (magnetIdx[idx - i - 1] + 2) % 8;

		if (magnet[idx - i][connectA] != magnet[idx - i - 1][connectB]) {
			int _dir = ((i + 1) % 2) ? -dir : dir;
			ret[idx - i - 1] = _dir;
		}
		else break;
	}

	// 오른쪽 자석들
	for (int i = 0; idx + i < 3; ++i) {
		int connectA = (magnetIdx[idx + i] + 2) % 8;
		int connectB = (magnetIdx[idx + i + 1] - 2 + 8) % 8;

		if (magnet[idx + i][connectA] != magnet[idx + i + 1][connectB]) {
			int _dir = ((i + 1) % 2) ? -dir : dir;
			ret[idx + i + 1] = _dir;
		}
		else break;
	}
	
	for (int i = 0; i < 4; ++i) {
		magnetIdx[i] = (magnetIdx[i] + ret[i] + 8) % 8;
	}
}

int calcScore() {
	int ret = 0;
	for (int i = 0; i < 4; ++i) {
		ret += (pow(2, i) * magnet[i][magnetIdx[i]]);
	}
	return ret;
}
//
//void printM() {
//	for (int i = 0; i < 4; ++i) {
//		cout << magnetIdx[i] << endl;
//	}
//}