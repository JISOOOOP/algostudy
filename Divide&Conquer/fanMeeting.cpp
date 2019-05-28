// ¹Ì¿Ï¼º


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> hyper, fans, result;

int calcHug();
int M2MTimes(int idx);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {

		string hyperStr, fanStr;
		
		// init && alloc
		cin >> hyperStr;
		for (int i = 0; i < hyperStr.size(); ++i) {
			hyper.push_back('M' == hyperStr[i]);
		}
		cin >> fanStr;
		for (int i = 0; i < fanStr.size(); ++i) {
			fans.push_back('M' == fanStr[i]);
		}
		reverse(hyper.begin(), hyper.end());

		result.push_back(calcHug());

		// free
		hyper.clear();
		fans.clear();
	}
	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}
int calcHug() {
	int rst = 0;

	for (int i = hyper.size() - 1; i < fans.size(); ++i) {
		if (!M2MTimes(i)) ++rst;
	}
	return rst;
}

int M2MTimes(int idx) {
	int ci = 0;
	int memberSize = hyper.size();

	for (int i = 0; i < memberSize; ++i) {
		ci += hyper[i] * fans[idx - i];
	}
	return ci;
}