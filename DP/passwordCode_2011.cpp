#include <iostream>
#include <vector>
#include <string>

#define MOD		  1000000

using namespace std;

string code;
vector<int> cache, result;

int decoder(int start);				// code[start]

int main() {

	//while (1) {
		// input & init & alloc
		cin >> code;
		//if (code[0] == '0' && code.size() == 1) break;

		for (int i = 0; i <= code.size(); ++i) {
			cache.push_back(0);
		}

		// proc
		result.push_back(decoder(0));

		// free
		cache.clear();
		code.clear();
	//}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int decoder(int start) {				// code[start]

	// base case
	if (start == code.size()) return 1;
	if (start > code.size()) return 0;

	// memoization
	int& ret = cache[start];
	if (ret) return ret;

	int num = (int)code[start] - 48;
	if (!num) return 0;

	// code[start]를 10자리로 쓸 경우
	int digit_10 = (int)code[start] - 48;
	int digit_1 = (int)code[start + 1] - 48;

	if (digit_10 * 10 + digit_1 <= 26) {
		ret += decoder(start + 2);
	}

	// code[start]를 1자리로 쓸 경우
	ret += decoder(start + 1);

	return ret %= MOD;
}