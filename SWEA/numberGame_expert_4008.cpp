#include <iostream>
#include <vector>

using namespace std;

// + - * /
vector<int> num, oper;

int numberGame_dfs_max(int idx, int cur);
int numberGame_dfs_min(int idx, int cur);


int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		//input
		int N;
		cin >> N;
		
		num = vector<int>(N, 0);
		oper = vector<int>(4, 0);
		for (int i = 0; i < 4; ++i) {
			cin >> oper[i];
		}

		for (int i = 0; i < N; ++i) {
			cin >> num[i];
		}

		// proc
		result[t] = 
			numberGame_dfs_max(1, num[0]) 
			- numberGame_dfs_min(1, num[0]);

		// free
		num.clear();
		oper.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int numberGame_dfs_max(int idx, int cur) {
	// base case
	if (idx == num.size()) return cur;

	int ret = -100000001;

	int temp = 0;
	// +
	if (oper[0] > 0) {
		--oper[0];
		temp = numberGame_dfs_max(idx + 1, cur + num[idx]);
		if (ret < temp) ret = temp;
		++oper[0];
	}
	// -
	if (oper[1] > 0) {
		--oper[1];
		temp = numberGame_dfs_max(idx + 1, cur - num[idx]);
		if (ret < temp) ret = temp;
		++oper[1];
	}
	// *
	if (oper[2] > 0) {
		--oper[2];
		temp = numberGame_dfs_max(idx + 1, cur * num[idx]);
		if (ret < temp) ret = temp;
		++oper[2];
	}
	// /
	if (num[idx] != 0 && oper[3] > 0) {
		--oper[3];
		temp = numberGame_dfs_max(idx + 1, cur / num[idx]);
		if (ret < temp) ret = temp;
		++oper[3];
	}

	return ret;
}

int numberGame_dfs_min(int idx, int cur) {
	// base case
	if (idx == num.size()) return cur;

	int ret = 100000001;

	int temp = 0;
	// +
	if (oper[0] > 0) {
		--oper[0];
		temp = numberGame_dfs_min(idx + 1, cur + num[idx]);
		if (ret > temp) ret = temp;
		++oper[0];
	}
	// -
	if (oper[1] > 0) {
		--oper[1];
		temp = numberGame_dfs_min(idx + 1, cur - num[idx]);
		if (ret > temp) ret = temp;
		++oper[1];
	}
	// *
	if (oper[2] > 0) {
		--oper[2];
		temp = numberGame_dfs_min(idx + 1, cur * num[idx]);
		if (ret > temp) ret = temp;
		++oper[2];
	}
	// /
	if (num[idx] != 0 && oper[3] > 0) {
		--oper[3];
		temp = numberGame_dfs_min(idx + 1, cur / num[idx]);
		if (ret > temp) ret = temp;
		++oper[3];
	}

	return ret;
}