#include <iostream>
#include <vector>

using namespace std;

// 0, up, right, down, left
const int dr[5] = { 0, -1, 0, 1, 0 };
const int dc[5] = { 0, 0, 1, 0, -1 };

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
};

struct BC {
	int r;
	int c;
	int range;
	int power;
};

vector<int> p1, p2;
vector<BC> ap;

int wireless(int M);
bool checkOverlap(vector<bool> en_p1, vector<bool> en_p2);
int findSingleMaxPower(vector<bool> en_p);
int calcMaxPower(vector<bool> en_p1, vector<bool> en_p2);
bool isEnable(int idx, pos p);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int M, A;
		cin >> M >> A;

		p1 = vector<int>(M + 1, 0);
		p2 = vector<int>(M + 1, 0);
		for (int i = 1; i <= M; ++i) {
			cin >> p1[i];
		}
		for (int i = 1; i <= M; ++i) {
			cin >> p2[i];
		}

		ap = vector<BC>(A);
		for (int i = 0; i < A; ++i) {
			cin >> ap[i].c >> ap[i].r >> ap[i].range >> ap[i].power;
		}

		// proc
		result[t] = wireless(M);

		// free
		p1.clear();
		p2.clear();
		ap.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int wireless(int M) {

	int ret = 0;
	pos cur_p1(1, 1), cur_p2(10, 10);
	pos next_p1 = cur_p1;
	pos next_p2 = cur_p2;

	for (int t = 0; t <= M; ++t) {
		next_p1.r += dr[p1[t]];
		next_p1.c += dc[p1[t]];

		next_p2.r += dr[p2[t]];
		next_p2.c += dc[p2[t]];

		// 충전 가능 AP 체크
		vector<bool> enable_p1(ap.size()), enable_p2(ap.size());
		for (int i = 0; i < ap.size(); ++i) {
			if (isEnable(i, next_p1)) enable_p1[i] = true;
			if (isEnable(i, next_p2)) enable_p2[i] = true;
		}

		if (checkOverlap(enable_p1, enable_p2)) {
			ret += calcMaxPower(enable_p1, enable_p2);
		}
		else {
			ret += findSingleMaxPower(enable_p1);
			ret += findSingleMaxPower(enable_p2);
		}
	}
	return ret;
}

// 겹치는게 있는지 확인
bool checkOverlap(vector<bool> en_p1, vector<bool> en_p2) {
	for (int i = 0; i < en_p1.size(); ++i) {
		if (en_p1[i] && en_p2[i]) return true;
	}
	return false;
}

// 가장 큰 BC 찾기
int findSingleMaxPower(vector<bool> en_p) {
	int ret = 0;
	for (int i = 0; i < en_p.size(); ++i) {
		if (en_p[i]) {
			int temp = ap[i].power;
			if (ret < temp) {
				ret = temp;
			}
		}
	}
	return ret;
}

// 겹치는 것 중 가장 큰 조합 찾기
int calcMaxPower(vector<bool> en_p1, vector<bool> en_p2) {
	vector<bool> visited(en_p1.size(), 0);
	int ret = 0;

	// 각각 다른 AP 쓰는 경우
	for (int i = 0; i < en_p1.size(); ++i) {
		if (en_p1[i]) {
			// backtracking
			visited[i] = 1;
			for (int j = 0; j < en_p2.size(); ++j) {
				if (en_p2[j] && !visited[j]) {
					int temp = ap[i].power + ap[j].power;
					if (ret < temp) {
						ret = temp;
					}
				}
			}
			visited[i] = 0;
		}
	}

	// 같은 AP 쓰는 경우
	for (int i = 0; i < en_p1.size(); ++i) {
		if (en_p1[i] && en_p2[i]) {
			int temp = ap[i].power;
			if (ret < temp) {
				ret = temp;
			}
		}
	}
	return ret;
}

bool isEnable(int idx, pos p) {
	bool ret;
	int dist = abs(p.r - ap[idx].r) + abs(p.c - ap[idx].c);
	ret = dist <= ap[idx].range ? true : false;
	return ret;
}