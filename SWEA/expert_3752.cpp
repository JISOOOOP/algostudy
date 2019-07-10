#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

bool visited[10001] = { false, };

vector<int> score;
vector< vector<int> > cache;

int proc(int N);
void dfs(int takenNum, int takenScore, int N, int& ret);

int main(){
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;

		score = vector<int>(N, 0);
		cache = vector< vector<int> >(101, vector<int>(10001, 0));
		for (int i = 0; i < N; ++i) {
			cin >> score[i];
		}

		// proc
		cout << "#" << t + 1 << " " << proc(N) << endl;

		// free
		score.clear();
		cache.clear();
		memset(visited, false, sizeof(visited));
	}
}

int proc(int N) {
	int ret = 0;
	dfs(0, 0, N, ret);
	return ret;
}

void dfs(int takenNum, int takenScore, int N, int& ret) {
	// base case
	if (takenNum == N) {
		if (visited[takenScore]) return;
		++ret;
		visited[takenScore] = true;
		return;
	}

	// memoization
	int& _ret = cache[takenNum][takenScore];
	if (_ret) return;

	_ret = true;

	dfs(takenNum + 1, takenScore + score[takenNum], N, ret);
	dfs(takenNum + 1, takenScore, N, ret);
}