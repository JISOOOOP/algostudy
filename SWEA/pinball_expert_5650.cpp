#include <iostream>
#include <vector>

using namespace std;

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

// 5 block, 4 direction
// up right down left order
const int block[6][4] = {
	{0 ,0 ,0 ,0},
	{2, 3, 1, 0},
	{1, 3, 0, 2},
	{3, 2, 0, 1},
	{2, 0, 3, 1},
	{2, 3, 0, 1}
};

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
	pos p;
	int dir;
	status(pos _p, int _d) {
		p = _p;
		dir = _d;
	}
};

vector< vector<int> > board;
vector< vector< vector<bool> > > visited;

int pinball();
void memoization(vector<status>& path);
vector<pos> findStartPos();
vector< vector<pos> > findWormHole();

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;

		board = vector< vector<int> >(N, vector<int>(N, 0));
		visited = vector< vector< vector<bool> > >(N, vector< vector<bool> >(N, vector<bool>(4, false)));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				scanf("%d", &board[i][j]);
			}
		}

		// proc
		result[t] = pinball();

		// free
		board.clear();
		visited.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int pinball() {
	int ret = 0;

	vector<pos> start = findStartPos();
	vector< vector<pos> > wormHole = findWormHole();

	for (int s = 0; s < start.size(); ++s) {
		pos startPoint = start[s];

		for (int i = 0; i < 4; ++i) {
			/*if (startPoint.r == 2 && startPoint.c == 2 && i == 1) {
				cout << endl;
			}*/
			if (visited[startPoint.r][startPoint.c][i]) continue;
			vector<bool> visitWormhole = vector<bool>(5, false);
			vector<status> path;
			int dir = i;
			path.push_back(status(startPoint, dir));
			int score = 0;
			int next_r = startPoint.r + dr[dir];
			int next_c = startPoint.c + dc[dir];

			while (next_r != startPoint.r || next_c != startPoint.c) {
				int next_dir = dir;
				// 벽 박는 경우(outOfRange)
				if (next_r < 0 || next_r >= board.size() || next_c < 0 || next_c >= board.size()) {
					// 방향 180도 회전
					next_dir = (dir + 2) % 4;
					++score;
				}
				// 블랙홀
				else if (board[next_r][next_c] == -1) break;
				// 벽돌 부딫친 경우
				else if (board[next_r][next_c] > 0 && board[next_r][next_c] < 6) {
					++score;
					next_dir = block[board[next_r][next_c]][dir];
				}
				// 윔홀
				else if (board[next_r][next_c] > 5 && board[next_r][next_c] < 11) {
					int holeNum = board[next_r][next_c] - 6;
					if (visitWormhole[holeNum]) break;
					visitWormhole[holeNum] = true;
					if (wormHole[board[next_r][next_c] - 6][0].r == next_r && wormHole[board[next_r][next_c] - 6][0].c == next_c) {
						next_r = wormHole[holeNum][1].r + dr[dir];
						next_c = wormHole[holeNum][1].c + dc[dir];
					}
					else {
						next_r = wormHole[holeNum][0].r + dr[dir];
						next_c = wormHole[holeNum][0].c + dc[dir];
					}
					continue;
				}
				// 방향 반대 되는 경우
				// 온길 돌아가므로 할 필요x, 메모이제이션 적용x
				if (next_dir == (dir + 2) % 4) {
					score = score * 2 - 1;
					break;
				}
				path.push_back(status(pos(next_r, next_c), dir));
				dir = next_dir;
				next_r += dr[dir];
				next_c += dc[dir];	
			}
			if (ret < score) ret = score;
			memoization(path);
			visitWormhole.clear();
		}
	}
	return ret;
}

void memoization(vector<status>& path) {
	for (int i = 0; i < path.size(); ++i) {
		visited[path[i].p.r][path[i].p.c][path[i].dir] = true;
	}
}

vector<pos> findStartPos() {
	vector<pos> ret;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board.size(); ++j) {
			if (board[i][j] == 0) {
				ret.push_back(pos(i, j));
			}
		}
	}
	return ret;
}

vector< vector<pos> > findWormHole() {
	vector< vector<pos> > ret(5 ,vector<pos>(2, pos(-1, -1)));
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board.size(); ++j) {
			if (board[i][j] > 5 && board[i][j] < 11) {
				if (ret[board[i][j] - 6][0].r == -1) {
					ret[board[i][j] - 6][0] = pos(i, j);
				}
				else {
					ret[board[i][j] - 6][1] = pos(i, j);
				}
			}
		}
	}
	return ret;
}