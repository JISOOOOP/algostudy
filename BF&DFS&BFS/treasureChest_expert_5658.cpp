#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int treasureChest(int N, int K, string passWord);
int convert(string str, int idx, int size);
bool isTaken(int num, vector<int>& arr, int size);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, K;
		cin >> N >> K;

		string passWord;
		cin >> passWord;

		// proc
		result[t] = treasureChest(N, K, passWord);

		// free
		passWord.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int treasureChest(int N, int K, string passWord) {
	int size = N / 4;
	vector<int> passInt(4 * size);
	int idx = 0;
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < 4; ++j) {
			int temp = convert(passWord, i + (j * size), size);
			if (!isTaken(temp, passInt, idx)) {
				passInt[idx++] = temp;
			}
		}
	}
	sort(passInt.begin(), passInt.end());
	return passInt[passInt.size() - K];
}

int convert(string str, int idx, int size) {
	int count = size - 1;
	int num = 0;
	for (int i = 0; i < size; ++i) {
		int _idx = (idx + i) % str.size();
		// 정수
		if (str[_idx] >= 48 && str[_idx] <= 57) {
			num += (str[_idx] - 48) * pow(16, count);
		}

		// 대문자
		else if (str[_idx] >= 65 && str[_idx] <= 90) {
			num += (str[_idx] - 65 + 10) * pow(16, count);
		}
		--count;
	}
	return num;
}

bool isTaken(int num, vector<int>& arr, int size) {
	for (int i = 0; i < size; ++i) {
		if (arr[i] == num) return true;
	}
	return false;
}