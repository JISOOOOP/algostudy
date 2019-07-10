#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector< vector<int> > bottle;

int honey(int M, int C);
int findMaxSum(vector< vector<int> >& sum, int& r, int& c);
void partialSumUnderC(vector< vector<int> >& sum, int M, int C);
int findMaxUnderC_dfs(int M, int C, int i, int j, int curSum);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, M, C;
		cin >> N >> M >> C;

		bottle = vector< vector<int> >(N, vector<int>(N, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> bottle[i][j];
			}
		}

		// proc
		result[t] = honey(M, C);

		// free
		bottle.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int honey(int M, int C) {

	vector< vector<int> > sum_M(bottle.size(), vector<int>(bottle.size(), 0));

	partialSumUnderC(sum_M, M, C);
	int r, c;
	int max1 = findMaxSum(sum_M, r, c);
	for (int i = 0; i < sum_M.size(); ++i) {
		sum_M[r][i] = 0;
	}
	int max2 = findMaxSum(sum_M, r, c);
	return max1 + max2;
}

int findMaxSum(vector< vector<int> >& sum, int& r, int& c) {
	int ret = 0;
	for (int i = 0; i < bottle.size(); ++i) {
		for (int j = 0; j < bottle.size(); ++j) {
			if (ret < sum[i][j]) {
				ret = sum[i][j];
				r = i;
				c = j;
			}
		}
	}
	return ret;
}

void partialSumUnderC(vector< vector<int> >& sum, int M, int C) {
	for (int i = 0; i < bottle.size(); ++i) {
		for (int j = 0; j < bottle.size() - M + 1; ++j) {
			sum[i][j] = findMaxUnderC_dfs(M, C, i, j, 0);
		}
	}
}

int findMaxUnderC_dfs(int M, int C, int i, int j, int curSum) {
	// base case
	if (curSum > C) return -100000000;
	if (M == 0) return 0;

	int ret = -1;

	int temp = 0;
	
	// bottle[i][j] 사용 x
	temp = findMaxUnderC_dfs(M - 1, C, i, j + 1, curSum);
	if (ret < temp) ret = temp;

	// bottle[i][j] 사용
	temp = pow(bottle[i][j], 2) + findMaxUnderC_dfs(M - 1, C, i, j + 1, curSum + bottle[i][j]);
	if (ret < temp) ret = temp;

	return ret;
}

// 문제 오류
// 같은 행에서 채취가 이루어 지지 않을 경우만 PASS
// 8 9 9 8 의 경우 9 9 선택해도 PASS