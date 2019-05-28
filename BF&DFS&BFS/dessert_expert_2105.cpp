#include <iostream>
#include <vector>

using namespace std;

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
};

// ����, ����, �»�, ���
const int dr[4] = { 1, 1, -1, -1 };
const int dc[4] = { 1, -1, -1, 1 };

vector< vector<int> > cafe, visited;

int dessert();
int calcMaxDessert(vector<int>& ate, pos start, pos cur, int direction);
bool isAte(vector<int>& ate, int dessert);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;

		// input && alloc
		cafe = vector< vector<int> >(N + 1, vector<int>(N + 1, 0));
		visited = vector< vector<int> >(N + 1, vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				scanf("%d", &cafe[i][j]);
			}
		}

		// proc
		result[t] = dessert();

		// free
		cafe.clear();
		visited.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();

}

int dessert() {
	int ret = -1;

	for (int i = 0; i < cafe.size() - 1; ++i) {
		for (int j = 0; j < cafe.size() - 1; ++j) {
			vector<int> ate;
			int temp = calcMaxDessert(ate, pos(i, j), pos(i, j), 0);
			if (temp > ret) ret = temp;
		}
	}
	return ret;
}

// ���� ���� �ð�������� ���� ���� ����
int calcMaxDessert(vector<int>& ate, pos start, pos cur, int direction) {
	// base case
	// �� �԰� ���������� ���ƿ��� ���
	if (!ate.empty() && (cur.r == start.r && cur.c == start.c)) return ate.size();
	
	// ���� ���̸�
	if (cur.r < 0 || cur.r >= cafe.size() - 1 || cur.c < 0 || cur.c >= cafe.size() - 1) return -1;

	// �Ծ��� �Ÿ� X
	if (isAte(ate, cafe[cur.r][cur.c])) return -1;

	int ret = -1;

	// �Դ� process
	ate.push_back(cafe[cur.r][cur.c]);

	int temp = 0;

	// ���� ���� ����
	pos next(cur.r + dr[direction], cur.c + dc[direction]);
	
	temp = calcMaxDessert(ate, start, next, direction);
	if (ret < temp) ret = temp;

	// �ð� �������� 90 ȸ�� ����
	temp = calcMaxDessert(ate, start, next, direction + 1);
	if (ret < temp) ret = temp;

	// back tracking
	ate.pop_back();
	
	return ret;
}

bool isAte(vector<int>& ate, int dessert) {
	for (int i = 0; i < ate.size(); ++i) {
		if (ate[i] == dessert) return true;
	}
	return false;
}