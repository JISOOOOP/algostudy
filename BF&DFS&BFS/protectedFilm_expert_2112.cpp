#include <iostream>
#include <vector>

using namespace std;

const int maxValue = 14;

vector< vector<int> > film;

void copyCell(vector<int>& src, vector<int>& dst, int size);
void protectFilm(int r, int chemicalCount, int K, int& ret);
void injectionChemical(int r, int chemical);
bool checkProtection(int K);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		int D, W, K;
		cin >> D >> W >> K;

		// input && alloc
		film = vector< vector<int> >(D + 1, vector<int>(W + 1, 0));
		for (int i = 0; i < D; ++i) {
			for (int j = 0; j < W; ++j) {
				scanf("%d", &film[i][j]);
			}
		}

		// proc
		int max = maxValue;
		protectFilm(0, 0, K, max);
		result[t] = max;

		// free
		film.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

void protectFilm(int r, int chemicalCount, int K, int& ret) {
	// base case
	// K == 1 �̸� 0
	if (K == 1) {
		ret = 0;
		return;
	}
	// ��ǰ ó���� ���� �ּڰ����� ������ ���
	if (chemicalCount > ret) return;
	// ��ȣ�� �� ���
	if (checkProtection(K)) {
		if (ret > chemicalCount) ret = chemicalCount;
		return;
	}
	// r�� ���� ����� �� ��� ���� ���
	if (r == film.size() - 1) return;

	// ���� ���� ����
	vector<int> origin(film[r].size());
	copyCell(film[r], origin, film[r].size());

	// ������ r��° ����
	// A �๰ ����
	injectionChemical(r, 0);
	protectFilm(r + 1, chemicalCount + 1, K, ret);
	// B �๰ ����
	injectionChemical(r, 1);
	protectFilm(r + 1, chemicalCount + 1, K, ret);
	// �������
	copyCell(origin, film[r], film[r].size());
	protectFilm(r + 1, chemicalCount, K, ret);
}

void copyCell(vector<int>& src, vector<int>& dst, int size) {
	for (int i = 0; i < size; ++i) {
		dst[i] = src[i];
	}
}

void injectionChemical(int r, int chemical) {
	for (int j = 0; j < film[0].size() - 1; ++j) {
		film[r][j] = chemical;
	}
}

bool checkProtection(int K) {
	int type, count;

	for (int j = 0; j < film[0].size() - 1; ++j) {
		type = film[0][j];
		count = 1;
		for (int i = 1; i < film.size() - 1; ++i) {
			if (type == film[i][j]) {
				++count;
				if (count >= K) break;
			}
			else {
				type = film[i][j];
				count = 1;
			}
		}
		if (count < K) return false;
	}
	return true;
}

// TLE
