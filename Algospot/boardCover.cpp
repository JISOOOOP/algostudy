#include <iostream>
#include <string>
#include <vector>

#define TURN_TYPE	4

using namespace std;

const int blockType[4][2][2] = {		// (r, c)
	{{0 ,1}, {1, 1}},
	{{1, 0}, {0, 1}},
	{{1, 0}, {1, 1}},
	{{1, 0}, {1, -1}}
};

vector< vector<int> > board;			// 게임판
vector<int> result;

int findWhiteBlock();					// white block 찾아서 index반환 없으면 -1
int matchingBlock();					// 4type의 블럭 넣을 수 있는지 확인, 되면 넣은상태에서 재귀

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {

		int H, W;
		scanf("%d %d", &H, &W);

		// init && alloc
		for (int h = 0; h < H; h++) {
			vector<int> ele(W);
			board.push_back(ele);
		}

		for (int h = 0; h < H; h++) {
			string str;
			cin >> str;
			for (int w = 0; w < W; w++) {
				char color = str[w];
				if (color == '#') board[h][w] = 1;						// black 1, white 0
				else if(color == '.') board[h][w] = 0;
			}
		}

		result.push_back(matchingBlock());

		//free
		board.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		printf("%d\n", result[i]);
	}

}

int matchingBlock() {					// 4type의 블럭 넣을 수 있는지 확인, 되면 넣은상태에서 재귀

	int r, c, dr1, dc1, dr2, dc2;

	int whiteIdx = findWhiteBlock();
	if (whiteIdx == -1) return 1;

	int rst = 0;
	int max_r = board.size();
	int max_c = board[0].size();

	r = whiteIdx / max_c;
	c = whiteIdx % max_c;

	for (int i = 0; i < TURN_TYPE; i++) {
		dr1 = r + blockType[i][0][0];
		dc1 = c + blockType[i][0][1];
		if (dr1 >= 0 && dr1 < max_r && dc1 >= 0 && dc1 < max_c && !board[dr1][dc1]) {
			dr2 = r + blockType[i][1][0];
			dc2 = c + blockType[i][1][1];
			if (dr2 >= 0 && dr2 < max_r && dc2 >= 0 && dc2 < max_c && !board[dr2][dc2]) {
				board[r][c] = 1;
				board[dr1][dc1] = 1;
				board[dr2][dc2] = 1;
				rst += matchingBlock();
				board[r][c] = 0;
				board[dr1][dc1] = 0;
				board[dr2][dc2] = 0;
			}
		}
	}
	return rst;
}

int findWhiteBlock() {						// white block 찾아서 index반환 없으면 -1
	
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (!board[i][j]) return (i * board[0].size()) + j;
		}
	}
	return -1;
}
