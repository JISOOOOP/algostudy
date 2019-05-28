#include <iostream>
#include <vector>

using namespace std;

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

void breakOut_dfs(vector< vector<int> >& block, int N, int W, int H, int& blockNum);
void blockDown(vector< vector<int> >& src);
void blockCrush(vector< vector<int> >& src, int c, int r);
int findHighest(vector< vector<int> >& src, int idx);
int calcBlockNum(vector< vector<int> >& src);
void copyBlock(vector< vector<int> >& src, vector< vector<int> >& dst);
bool isZero(vector< vector<int> >& src, int idx);
bool isEmpty(vector< vector<int> >& src);
void printBlock(vector< vector<int> >& src);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, W, H;
		cin >> N >> W >> H;

		vector< vector<int> > block(H, vector<int>(W, 0));
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				cin >> block[i][j];
			}
		}

		// proc
		int blockNum = 12 * 15 + 1;
		breakOut_dfs(block, N, W, H, blockNum);
		result[t] = blockNum;

		// free
		block.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

void breakOut_dfs(vector< vector<int> >& block, int N, int W, int H, int& blockNum) {
	// base case
	if (N == 0) {
		int temp = calcBlockNum(block);
		if (blockNum > temp) blockNum = temp;
		return;
	}
	if (isEmpty(block)) {
		blockNum = 0;
		return;
	}

	vector< vector<int> > copy(H, vector<int>(W, 0));

	for (int i = 0; i < W; ++i) {
		// 현재 상태 저장
		copyBlock(block, copy);
		int highest = findHighest(block, i);
		if (highest != -1) {
			blockCrush(copy, i, highest);
			blockDown(copy);
			breakOut_dfs(copy, N - 1, W, H, blockNum);
		}
	}
	copy.clear();
}

// 빈 블록인지
bool isEmpty(vector< vector<int> >& src) {
	for (int i = 0; i < src[0].size(); ++i) {
		if (src[src.size() - 1][i] != 0) return false;
	}
	return true;
}

// 블록 정리
void blockDown(vector< vector<int> >& src) {
	for (int j = 0; j < src[0].size(); ++j) {
		for (int i = src.size() - 1; i > 0; --i) {
			if (src[i][j] == 0) {
				int r;
				for (r = i; r >= 0; --r) {
					if (src[r][j] != 0) break;
				}
				if (r == -1) break;
				src[i][j] = src[r][j];
				src[r][j] = 0;
			}
		}
	}
}

bool isZero(vector< vector<int> >& src, int idx) {
	for (int i = idx; i >= 0; --i) {
		if (src[i][idx] != 0) return false;
	}
	return true;
}

// 블록 깨기
void blockCrush(vector< vector<int> >& src, int c, int r) {
	int range = src[r][c];
	src[r][c] = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j < range; ++j) {
			int next_r = r + (dr[i] * j);
			int next_c = c + (dc[i] * j);
			// outOfRange
			if (next_r < 0 || next_r >= src.size() || next_c < 0 || next_c >= src[0].size()) break;
			blockCrush(src, next_c, next_r);
		}
	}
}

int findHighest(vector< vector<int> >& src, int idx) {
	// 맨 밑이 0이면 그 위로 다 0, -1 empty
	if (src[src.size() - 1][idx] == 0) return -1;
	for (int i = 0; i < src.size(); ++i) {
		if (src[i][idx] != 0) return i;
	}
}

int calcBlockNum(vector< vector<int> >& src) {
	int ret = 0;
	for (int i = 0; i < src.size(); ++i) {
		for (int j = 0; j < src[0].size(); ++j) {
			if (src[i][j] != 0) ++ret;
		}
	}
	return ret;
}

void copyBlock(vector< vector<int> >& src, vector< vector<int> >& dst) {
	for (int i = 0; i < src.size(); ++i) {
		for (int j = 0; j < src[0].size(); ++j) {
			dst[i][j] = src[i][j];
		}
	}
}

void printBlock(vector< vector<int> >& src) {
	for (int i = 0; i < src.size(); ++i) {
		for (int j = 0; j < src[0].size(); ++j) {
			printf("%d ", src[i][j]);
		}
		cout << endl;
	}
}