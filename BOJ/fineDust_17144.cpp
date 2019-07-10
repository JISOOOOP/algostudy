#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct pos {
	int r;
	int c;
	pos(int _r, int _c) {
		r = _r;
		c = _c;
	}
};

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

vector< vector< vector<int> > > room;

int fineDust(int T);
int calcDust(int T);
void cleanerCycle(vector<pos> cleaner, int idx);
void memsetZero(int idx);
void dustSpread(int idx);
vector<pos> findCleaner();
void printRoom(int idx);

int main() {
	// input
	int R, C, T;
	cin >> R >> C >> T;

	room = vector< vector< vector<int> > >(2, vector< vector<int> >(R, vector<int>(C, 0)));
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> room[0][i][j];
		}
	}

	// proc
	cout << fineDust(T);

	// free
	room.clear();
}

int fineDust(int T) {
	vector<pos> cleaner = findCleaner();

	for (int t = 0; t < T; ++t) {
		dustSpread(t % 2);
		/*printRoom((t + 1) % 2);
		cout << endl;*/
		cleanerCycle(cleaner, (t + 1) % 2);
		/*printRoom((t + 1) % 2);
		cout << endl;*/
		memsetZero(t % 2);
	}
	return calcDust(T);
}

int calcDust(int T) {
	int ret = 0;
	int idx = T % 2;
	for (int i = 0; i < room[0].size(); ++i) {
		for (int j = 0; j < room[0][0].size(); ++j) {
			if (room[idx][i][j] >= 0) ret += room[idx][i][j];
		}
	}
	return ret;
}

void cleanerCycle(vector<pos> cleaner, int idx) {
	queue<int> q;
	int cleaner_r = cleaner[0].r;
	int cleaner_c = cleaner[0].c;
	// firstCleaner
	q.push(0);
	// right
	for (int c = 1; c < room[0][0].size(); ++c) {
		q.push(room[idx][cleaner_r][c]);
	}
	// up
	for (int r = cleaner_r - 1; r >= 0; --r) {
		q.push(room[idx][r][room[0][0].size() - 1]);
	}
	// left
	for (int c = room[0][0].size() - 2; c >= 0; --c) {
		q.push(room[idx][0][c]);
	}
	// down
	for (int r = 1; r <= cleaner_r - 2; ++r) {
		q.push(room[idx][r][0]);
	}

	// right
	for (int c = 1; c < room[0][0].size(); ++c) {
		room[idx][cleaner_r][c] = q.front();
		q.pop();
	}
	// up
	for (int r = cleaner_r - 1; r >= 0; --r) {
		room[idx][r][room[0][0].size() - 1] = q.front();
		q.pop();
	}
	// left
	for (int c = room[0][0].size() - 2; c >= 0; --c) {
		room[idx][0][c] = q.front();
		q.pop();
	}
	// down
	for (int r = 1; r <= cleaner_r - 1; ++r) {
		room[idx][r][0] = q.front();
		q.pop();
	}

	// secondCleaner
	cleaner_r = cleaner[1].r;
	cleaner_c = cleaner[1].c;
	q.push(0);
	// right
	for (int c = 1; c < room[0][0].size(); ++c) {
		q.push(room[idx][cleaner_r][c]);
	}
	// down
	for (int r = cleaner_r + 1; r < room[0].size(); ++r) {
		q.push(room[idx][r][room[0][0].size() - 1]);
	}
	// left
	for (int c = room[0][0].size() - 2; c >= 0; --c) {
		q.push(room[idx][room[0].size() - 1][c]);
	}
	// up
	for (int r = room[0].size() - 2; r >= cleaner_r + 2; --r) {
		q.push(room[idx][r][0]);
	}

	// right
	for (int c = 1; c < room[0][0].size(); ++c) {
		room[idx][cleaner_r][c] = q.front();
		q.pop();
	}
	// down
	for (int r = cleaner_r + 1; r < room[0].size(); ++r) {
		room[idx][r][room[0][0].size() - 1] = q.front();
		q.pop();
	}
	// left
	for (int c = room[0][0].size() - 2; c >= 0; --c) {
		room[idx][room[0].size() - 1][c] = q.front();
		q.pop();
	}
	// up
	for (int r = room[0].size() - 2; r >= cleaner_r + 1; --r) {
		room[idx][r][0] = q.front();
		q.pop();
	}
}

void memsetZero(int idx) {
	for (int i = 0; i < room[0].size(); ++i) {
		for (int j = 0; j < room[0][0].size(); ++j) {
			room[idx][i][j] = 0;
		}
	}
}

void dustSpread(int idx) {
	int nextIdx = (idx + 1) % 2;
	for (int i = 0; i < room[0].size(); ++i) {
		for (int j = 0; j < room[0][0].size(); ++j) {
			if (room[idx][i][j] >= 5) {
				int spreadCount = 0;
				int spread = room[idx][i][j] / 5;
				for (int d = 0; d < 4; ++d) {
					int next_r = i + dr[d];
					int next_c = j + dc[d];
					// outOfRange
					if (next_r < 0 || next_r >= room[0].size() || next_c < 0 || next_c >= room[0][0].size()) continue;
					// cleaner
					if (room[idx][next_r][next_c] == -1) continue;
					room[nextIdx][next_r][next_c] += spread;
					++spreadCount;
				}
				room[nextIdx][i][j] += room[idx][i][j] - (spread * spreadCount);
			}
			else {
				room[nextIdx][i][j] += room[idx][i][j];
			}
		}
	}
}

vector<pos> findCleaner() {
	vector<pos> ret;
	for (int i = 0; i < room[0].size(); ++i) {
		for (int j = 0; j < room[0][0].size(); ++j) {
			if (room[0][i][j] == -1) {
				ret.push_back(pos(i, j));
				ret.push_back(pos(i + 1, j));
				return ret;
			}
		}
	}
}

//// debug
//void printRoom(int idx) {
//	for (int i = 0; i < room[0].size(); ++i) {
//		for (int j = 0; j < room[0][0].size(); ++j) {
//			printf("%3d", room[idx][i][j]);
//		}
//		printf("\n");
//	}
//}