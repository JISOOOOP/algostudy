#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > field;

int runway(int X);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, X;
		cin >> N >> X;

		field = vector< vector<int> >(N + 1, vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> field[i][j];
			}
		}

		// proc
		result[t] = runway(X);

		// free
		field.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int runway(int X) {
	int ret = 0;
	// 가로
	for (int i = 0; i < field.size() - 1; ++i) {
		int height, count = 1;
		height = field[i][0];
		int j;
		for (j = 1; j < field.size() - 1; ++j) {
			if (height == field[i][j]) ++count;
			else {
				int dif = field[i][j] - height;
				// 높이 1 넘게 차이나면 불가능
				if (abs(dif) != 1) break;
				// 높을때
				if (height < field[i][j]) {
					// 경사로 설치 불가능
					if (count < X) break;
					height = field[i][j];
					count = 1;
				}
				// 낮을때
				else {
					height = field[i][j];
					int skip;
					for (skip = 1; skip <= X; ++skip) {
						// outOfRange
						if (j + skip >= field.size() - 1) break;
						if (height != field[i][j + skip]) break;
					}
					if (skip < X) break;
					j += X - 1;
					count = 0;
				}
			}
		}
		if (j == field.size() - 1) ++ret;
	}

	// 세로
	for (int j = 0; j < field.size() - 1; ++j) {
		int height, count = 1;
		height = field[0][j];
		int i;
		for (i = 1; i < field.size() - 1; ++i) {
			if (height == field[i][j]) ++count;
			else {
				int dif = field[i][j] - height;
				// 높이 1 넘게 차이나면 불가능
				if (abs(dif) != 1) break;
				// 높을때
				if (height < field[i][j]) {
					// 경사로 설치 불가능
					if (count < X) break;
					height = field[i][j];
					count = 1;
				}
				// 낮을때
				else {
					height = field[i][j];
					int skip;
					for (skip = 1; skip <= X; ++skip) {
						// outOfRange
						if (i + skip >= field.size() - 1) break;
						if (height != field[i + skip][j]) break;

					}
					if (skip < X) break;
					i += X - 1;
					count = 0;
				}
			}
		}
		if (i == field.size() - 1) ++ret;
	}
	return ret;
}