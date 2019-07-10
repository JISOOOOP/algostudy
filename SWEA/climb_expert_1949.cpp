#include <iostream>
#include <vector>

using namespace std;

struct pos {
	int r;
	int c;

	pos(int r_, int c_) {
		r = r_;
		c = c_;
	}
};

// up, right, down, left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

int climb(vector< vector<int> >& mountain, int K);
int maxClimbRoad(vector< vector<int> >& mountain, vector< vector<bool> >& visited, int start_r, int start_c, int enable_K, int K);
vector<pos> findMaxHeight(vector< vector<int> >& mountain);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		int N, K;
		cin >> N >> K;

		// input && alloc
		vector< vector<int> > mountain;
		mountain = vector< vector<int> >(N + 1, vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> mountain[i][j];
			}
		}

		result[t] = climb(mountain, K);
	}
	// print result
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int climb(vector< vector<int> >& mountain, int K) {

	vector<pos> maxHeight;
	vector< vector<bool> > visited;
	visited = vector< vector<bool> >(mountain.size(), vector<bool>(mountain.size() , 0));
	int ret = 0;

	maxHeight = findMaxHeight(mountain);
	for (int i = 0; i < maxHeight.size(); ++i) {
		int start_r = maxHeight[i].r;
		int start_c = maxHeight[i].c;
		int temp = maxClimbRoad(mountain, visited, start_r, start_c, 0, K);
		if (ret < temp) ret = temp;
	}
	
	return ret;
}

// start���� �����ϴ� ���� �� ���� 
int maxClimbRoad(vector< vector<int> >& mountain, vector< vector<bool> >& visited, int start_r, int start_c, int enable_K, int K) {
	int ret = 1;

	int size = mountain.size() - 1;
	int curHeight = mountain[start_r][start_c];

	// back tracking
	visited[start_r][start_c] = 1;

	// 4���� Ž��
	for (int i = 0; i < 4; ++i) {
		int next_r = start_r + dr[i];
		int next_c = start_c + dc[i];
		if (next_r >= 0 && next_r < size && next_c >= 0 && next_c < size && !visited[next_r][next_c]) {
			// ���̰� ���� ���
			if (curHeight > mountain[next_r][next_c]) {
				int temp = 1 + maxClimbRoad(mountain, visited, next_r, next_c, enable_K, K);
				if (ret < temp) ret = temp;
			}
			// ���̰� ���ų� ū ���
			// �ִ� K ��ŭ ���� enable_K = 1
			else {	
				// K�� ���� �Ƚ��� ���
				if (!enable_K) {
					int dist = mountain[next_r][next_c] - curHeight + 1;
					// ������ + 1��ŭ �� �� �ִ� ���
					if (K >= dist) {
						// back tracking
						mountain[next_r][next_c] -= dist;
						int temp = 1 + maxClimbRoad(mountain, visited, next_r, next_c, 1, K);
						if (ret < temp) ret = temp;
						mountain[next_r][next_c] += dist;
					}
				}
			}
		}
	}
	visited[start_r][start_c] = 0;
	return ret;
}

vector<pos> findMaxHeight(vector< vector<int> >& mountain) {
	vector<pos> ret;
	int maxHeight = 0;

	for (int i = 0; i < mountain.size(); ++i) {
		for (int j = 0; j < mountain.size(); ++j) {
			if (maxHeight < mountain[i][j]) {
				ret.clear();
				ret.push_back(pos(i, j));
				maxHeight = mountain[i][j];
			}
			else if(maxHeight == mountain[i][j]) ret.push_back(pos(i, j));
		}
	}
	return ret;
}