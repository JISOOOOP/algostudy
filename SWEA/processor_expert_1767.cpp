#include <iostream>
#include <vector>

using namespace std;

struct LOCATION {
	int r;
	int c;
};

struct RET {
	int core;
	int line;
};

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

RET processor(vector< vector<int> >& board, vector<LOCATION> core, int coreIdx);
vector<LOCATION> findCore(vector< vector<int> >& board);
bool checkLine(vector< vector<int> >& board, LOCATION start, int mode);
int drawLine(vector< vector<int> >& board, LOCATION start, int mode);
void eraseLine(vector< vector<int> >& board, LOCATION start, int mode);
int min(int a, int b);
int max(int a, int b);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		// init && alloc
		int N;
		cin >> N;

		vector< vector<int> > board;
		for (int n = 0; n <= N; ++n) {
			vector<int> ele(N + 1, 0);
			board.push_back(ele);
		}

		// input
		// 0 empty, 1 core, 2 line
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				scanf("%d", &board[i][j]);
			}
		}

		// proc
		LOCATION start;
		start.r = 0; start.c = 0;
		vector<LOCATION> core = findCore(board);
		RET ret = processor(board, core, 0);
		result[t] = ret.line;

		// free
		board.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << "#" << i + 1 << " " << result[i] << endl;
	}

	// result free
	result.clear();
}

RET processor(vector< vector<int> >& board, vector<LOCATION> core, int coreIdx) {
	LOCATION current;
	RET ret, temp, next;
	ret.core = 0, ret.line = 0;
	temp.core = 0; temp.line = 0;
	// base case
	if (coreIdx >= core.size()) return ret;
	current.r = core[coreIdx].r;
	current.c = core[coreIdx].c;

	// 4방향 선 긋기 경우
	for (int i = 0; i < 4; ++i) {
		// 선 그릴 수 있는지 확인
		if (!checkLine(board, current, i)) continue;
		// backTracking
		int lineCount = drawLine(board, current, i);
		next = processor(board, core, coreIdx + 1);
		temp.core = 1 + next.core;
		temp.line = lineCount + next.line;
		// max core && min line
		if (ret.core < temp.core) ret = temp;
		else if (ret.core == temp.core) ret.line = min(ret.line, temp.line);
		// BackTracking
		eraseLine(board, current, i);
	}
	// core 안쓰는 경우
	temp = processor(board, core, coreIdx + 1);
//	if (testCode == 0) cout << temp.core << ' ' << temp.line << endl;
	if (ret.core < temp.core) ret = temp;
	else if (ret.core == temp.core) ret.line = min(ret.line, temp.line);

	return ret;
}

// core 위치 반환(vector)
// 테두리는 계산할 필요 x
vector<LOCATION> findCore(vector< vector<int> >& board) {
	vector<LOCATION> ret;
	int size = board.size() - 1;
	for (int i = 1; i < size - 1; ++i) {
		for (int j = 1; j < size - 1; ++j) {
			if (board[i][j] == 1) {
				LOCATION temp;
				temp.r = i;
				temp.c = j;
				ret.push_back(temp);
			}
		}
	}
	return ret;
}

// 선 그릴 수 있는지 check
bool checkLine(vector< vector<int> >& board, LOCATION start, int mode) {
	int next_r = start.r + dr[mode];
	int next_c = start.c + dc[mode];
	int size = board.size() - 1;

	while (next_r >= 0 && next_r < size && next_c >= 0 && next_c < size) {
		if (board[next_r][next_c] != 0) return false;
		next_r += dr[mode];
		next_c += dc[mode];
	}
	return true;
}

// 선 연결, 중간에 뭐 있으면 false 반환
// 0 up, 1 right, 2 down, 3 left
int drawLine(vector< vector<int> >& board, LOCATION start, int mode) {
	int next_r = start.r + dr[mode];
	int next_c = start.c + dc[mode];
	int size = board.size() - 1;
	int ret = 0;

	while (next_r >= 0 && next_r < size && next_c >= 0 && next_c < size) {
		board[next_r][next_c] = 2;
		++ret;
		next_r += dr[mode];
		next_c += dc[mode];
	}
	return ret;
}

// 연결 된 선 삭제
// 0 up, 1 right, 2 down, 3 left
void eraseLine(vector< vector<int> >& board, LOCATION start, int mode) {

	int next_r = start.r + dr[mode];
	int next_c = start.c + dc[mode];
	int size = board.size() - 1;

	while (next_r >= 0 && next_r < size && next_c >= 0 && next_c < size) {
		board[next_r][next_c] = 0;
		next_r += dr[mode];
		next_c += dc[mode];
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void prinfboard(vector< vector<int> >& board) {
	cout << endl;
	for (int i = 0; i < board.size() - 1; ++i) {
		for (int j = 0; j < board.size() - 1; ++j) {
			printf("%d ", board[i][j]);
		}
		cout << endl;
	}
}