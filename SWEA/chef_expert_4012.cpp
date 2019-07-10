#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > src;
vector<bool> visited;

int chef();
int selectSrc(int idx, int selectNum, vector<int>& src1, vector<int>& src2);
void pushRemain(vector<int>& src2);
int calcDiff(vector<int>& src1);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;

		src = vector< vector<int> >(N, vector<int>(N, 0));
		visited = vector<bool>(N, false);
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> src[i][j];
			}
		}

		// proc
		result[t] = chef();

		// free
		src.clear();
		visited.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int chef() {
	int selecNum = src.size() / 2;

	vector<int> src1, src2;
	return selectSrc(0, selecNum, src1, src2);
}

int selectSrc(int idx, int selectNum, vector<int>& src1, vector<int>& src2) {
	// base case
	if (idx + selectNum > src.size()) return 20001;
	if (selectNum == 0) {
		pushRemain(src2);
		int temp = abs(calcDiff(src1) - calcDiff(src2));
		src2.clear();
		return temp;
	}

	int ret = 20001;

	int temp = 0;
	// non-selec idx
	temp = selectSrc(idx + 1, selectNum, src1, src2);
	if (temp < ret) ret = temp;

	// back tracking
	// selec idx
	visited[idx] = true;
	src1.push_back(idx);
	temp = selectSrc(idx + 1, selectNum - 1, src1, src2);
	visited[idx] = false;
	src1.pop_back();
	if (temp < ret) ret = temp;

	return ret;
}

// 남은거 src2에 다 넣기
void pushRemain(vector<int>& src2) {
	for (int i = 0; i < src.size(); ++i) {
		if (!visited[i]) src2.push_back(i);
	}
}

// 시너지 합
int calcDiff(vector<int>& src1) {
	int sum = 0;
	for (int i = 0; i < src.size() / 2 - 1; ++i) {
		for (int j = i + 1; j < src.size() / 2; ++j) {
			sum += (src[src1[i]][src1[j]] + src[src1[j]][src1[i]]);
		}
	}
	return sum;
}