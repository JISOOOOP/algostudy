#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// up down left right
const int dr[4] = { -1, 1, 0, 0 };
const int dc[4] = { 0, 0, -1, 1 };

struct micro {
	int microNum;
	int dir;
	micro(int _microNum, int _dir) {
		microNum = _microNum;
		dir = _dir;
	}
	micro(){}
};

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
};

vector < vector< vector<micro> > > cell;
vector < vector< micro> > visited;

int microbialIsolation(int M, queue<pos>& microPos);
bool checkIsolationSection(pos cur);
void memsetZero(vector< vector<micro> >& arr);
int calcMicroNum(int M);
void printCell(int idx);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		// input && alloc
		int N, M, K;
		cin >> N >> M >> K;
		cell = vector< vector< vector<micro> >>(2, vector< vector<micro> >(N + 1, vector<micro>(N + 1, micro(0, 0))));
		visited = vector< vector<micro> >(N + 1, vector<micro>(N + 1, micro(0, 0)));
		queue<pos> microPos;
		for (int k = 0; k < K; ++k) {
			int temp_r, temp_c;
			cin >> temp_r >> temp_c;
			cin >> cell[0][temp_r][temp_c].microNum >> cell[0][temp_r][temp_c].dir;
			--cell[0][temp_r][temp_c].dir;
			microPos.push(pos(temp_r, temp_c));
		}

		// proc
		result[t] = microbialIsolation(M, microPos);

		// free
		cell.clear();
		visited.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int microbialIsolation(int M, queue<pos>& microPos) {

	vector<pos> temp;

	for (int i = 0; i < M; ++i) {
		// slide window
		int idx = i % 2;

		while (!microPos.empty()) {
			pos cur = microPos.front();
			microPos.pop();

			// 격리 구역일 때
			if (checkIsolationSection(cur)) {
				if (cell[idx][cur.r][cur.c].dir < 2) {
					cell[idx][cur.r][cur.c].dir = (cell[idx][cur.r][cur.c].dir + 1) % 2;
				}
				else {
					cell[idx][cur.r][cur.c].dir = (cell[idx][cur.r][cur.c].dir + 1) % 2 + 2;
				}
			}

			int next_r = cur.r + dr[cell[idx][cur.r][cur.c].dir];
			int next_c = cur.c + dc[cell[idx][cur.r][cur.c].dir];

			// proc
			int next_microNum, next_dir;
			// 다음 갈 곳이
			// 중복되는 미생물 있는지
			if (visited[next_r][next_c].microNum == 0) {
				// 격리 구역인지
				if (checkIsolationSection(pos(next_r, next_c))) {
					next_microNum = cell[idx][cur.r][cur.c].microNum / 2;
				}
				else {
					next_microNum = cell[idx][cur.r][cur.c].microNum;
				}
				next_dir = cell[idx][cur.r][cur.c].dir;
				cell[(idx + 1) % 2][next_r][next_c].microNum = visited[next_r][next_c].microNum = next_microNum;
				cell[(idx + 1) % 2][next_r][next_c].dir = visited[next_r][next_c].dir = next_dir;
				if (cell[(idx + 1) % 2][next_r][next_c].microNum != 0) temp.push_back(pos(next_r, next_c));
			}
			else {
				// microNum 비교
				if (visited[next_r][next_c].microNum < cell[idx][cur.r][cur.c].microNum) {
					visited[next_r][next_c].microNum = cell[idx][cur.r][cur.c].microNum;
					visited[next_r][next_c].dir = cell[(idx + 1) % 2][next_r][next_c].dir = cell[idx][cur.r][cur.c].dir;
				}
				cell[(idx + 1) % 2][next_r][next_c].microNum += cell[idx][cur.r][cur.c].microNum;
			}
		}

		/*printCell((idx + 1) % 2);
		cout << endl;*/

		memsetZero(visited);
		memsetZero(cell[idx]);

		// 다음 미생물 위치 큐에 옮기기
		for (int i = 0; i < temp.size(); ++i) {
			microPos.push(temp[i]);
		}
		temp.clear();
	}
	return calcMicroNum(M);
}

bool checkIsolationSection(pos cur) {
	if (cur.r == 0 || cur.r == cell[0].size() - 2 || cur.c == 0 || cur.c == cell[0].size() - 2) {
		return true;
	}
	return false;
}

void memsetZero(vector< vector<micro> >& arr) {
	for (int i = 0; i < arr.size() - 1; ++i) {
		for (int j = 0; j < arr.size() - 1; ++j) {
			arr[i][j].microNum = 0;
			arr[i][j].dir = 0;
		}
	}
}

int calcMicroNum(int M) {
	int ret = 0;
	
	for (int i = 0; i < cell[0].size() - 1; ++i) {
		for (int j = 0; j < cell[0].size() - 1; ++j) {
			ret += cell[M % 2][i][j].microNum;
		}
	}

	return ret;
}

void printCell(int idx) {
	for (int i = 0; i < cell[0].size() - 1; ++i) {
		for (int j = 0; j < cell[0].size() - 1; ++j) {
			printf("%5d ", cell[idx][i][j]);
		}
		cout << endl;
	}
}