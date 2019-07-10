#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> result;
string str;

string rvrs_quadTree(int *idx);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		cin >> str;

		int idx = 0;
		result.push_back(rvrs_quadTree(&idx));
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

string rvrs_quadTree(int *idx) {

	string rst, str1_2, str3_4;
	// base condition, idx 자리가 x가 아니면
	if (str[*idx] != 'x') return rst += str[*idx];

	for (int i = 0; i < 4; i++) {		// x빼고 3 4 1 2 순서로 붙이기
		char temp = str[++(*idx)];
		if (temp == 'x') {
			if (i < 2) str1_2 += rvrs_quadTree(idx);
			else str3_4 += rvrs_quadTree(idx);
		}
		else {
			if (i < 2) str1_2 += temp;
			else str3_4 += temp;
		}
	}
	return rst = 'x' + str3_4 + str1_2;
}