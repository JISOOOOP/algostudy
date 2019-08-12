#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > board;
vector< vector<int> > visited;

int main() {
	int H, W, N;
	cin >> H >> W >> N;

	board = vector< vector<int> >(H + 2, vector<int>(W + 2, 0));
	visited = vector< vector<int> >(H + 2, vector<int>(W + 2, 0));
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			scanf("%d", &board[i][j]);
		}
	}

	visited[1][1] = N - 1;
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			if (visited[i][j] == 0) continue;

			visited[i + 1][j] += visited[i][j] / 2;
			visited[i][j + 1] += visited[i][j] / 2;
			if (visited[i][j] % 2 == 1) {
				if (board[i][j] == 1) ++visited[i][j + 1];
				else ++visited[i + 1][j];
			}

			board[i][j] = (board[i][j] + visited[i][j]) % 2;
		}
	}

	int r = 1, c = 1;
	while (r <= H && c <= W) {
		if (board[r][c] == 1) ++c;
		else ++r;
	}

	cout << r << ' ' << c << endl;
}
