#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
	pos() {};
};

struct status {
	pos loc;
	int cellNum;
	int actCount;
	int deactCount;
	// 0 비활성, 1 활성, 2 증식 했음
	int cellStatus;
	status(pos l, int c) {
		loc = l;
		cellNum = actCount = deactCount = c;
		cellStatus = 0;
	}
};

// -1 died, 0 empty, other actCell
vector< vector<int> > cell;

int shootCulture(pos start, int N, int M, int K);
queue<status> findActCell(pos start, int N, int M);
void printCell();

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, M, K;
		cin >> N >> M >> K;

		int size = 300 + 50 + 50;
		cell = vector< vector<int> >(size, vector<int>(size, 0));
		int start_r = size / 2 - (N / 2);
		int start_c = size / 2 - (M / 2);
		pos start(start_r, start_c);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				scanf("%d", &cell[start_r + i][start_c + j]);
			}
		}

		// proc
		result[t] = shootCulture(start, N, M, K);

		// free
		cell.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int shootCulture(pos start, int N, int M, int K) {

	int size = 300 + 50 + 50;
	queue<status> actCell = findActCell(start, N, M);
	vector< vector<bool> > visited = vector< vector<bool> >(size, vector<bool>(size, false));

	for (int k = 0; k < K; ++k) {
		vector<status> nextStep;

		while (!actCell.empty()) {
			status cur = actCell.front();
			actCell.pop();

			// 비활성 상태일 경우
			if (cur.cellStatus == 0) {
				cur.deactCount -= 1;
				if (cur.deactCount == 0) cur.cellStatus = 1;
				nextStep.push_back(cur);
				continue;
			}
			// 활성 상태일 경우
			if (cur.cellStatus != 0) {
				// 활성 상태면서 증식 한번도 안한 경우
				if (cur.cellStatus == 1) {
					// 배양
					for (int i = 0; i < 4; ++i) {
						int next_r = cur.loc.r + dr[i];
						int next_c = cur.loc.c + dc[i];

						// 빈 공간 배양
						if (cell[next_r][next_c] == 0) {
							status temp(pos(next_r, next_c), cur.cellNum);
							visited[next_r][next_c] = true;
							cell[next_r][next_c] = cur.cellNum;
							nextStep.push_back(temp);
						}
						// 동시에 접근하는 경우
						else {
							// 이번 단계에 바뀐거고 더 작으면
							if (visited[next_r][next_c] && cell[next_r][next_c] < cur.cellNum) {
								// nextStep에서 찾기
								for (int i = 0; i < nextStep.size(); ++i) {
									if (nextStep[i].loc.r == next_r && nextStep[i].loc.c == next_c) {
										nextStep[i].actCount = nextStep[i].cellNum = nextStep[i].deactCount = cell[next_r][next_c] = cur.cellNum;
									}
								}
							}
						}
					}
					cur.cellStatus = 2;
				}
				cur.actCount -= 1;
				if (cur.actCount <= 0) {
					cell[cur.loc.r][cur.loc.c] = -1;
				}
				else {
					nextStep.push_back(cur);
				}
			}
		}
		// nextStep -> queue, visited init
		for (int i = 0; i < nextStep.size(); ++i) {
			actCell.push(nextStep[i]);
			visited[nextStep[i].loc.r][nextStep[i].loc.c] = false;
		}
		nextStep.clear();
		/*cout << endl;
		printCell();*/
	}
	visited.clear();
	return actCell.size();
}

queue<status> findActCell(pos start, int N, int M) {
	queue<status> ret;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (cell[start.r + i][start.c + j] != 0) {
				status temp(pos(start.r + i, start.c + j), cell[start.r + i][start.c + j]);
				ret.push(temp);
			}
		}
	}
	return ret;
}

void printCell() {
	for (int i = 190; i < 220; ++i) {
		for (int j = 190; j < 220; ++j) {
			printf("%3d", cell[i][j]);
		}
		printf("\n");
	}
}