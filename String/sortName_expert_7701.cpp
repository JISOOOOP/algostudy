#include <iostream>
#include <vector>
#include <string>
#include <queue>

#define MAX_NAME 20001

using namespace std;

vector<string> nameList;
vector<int> nameLen;
vector< queue<string> > radix(26);

void sortName();
void radixSort(int len, int listStart);
void calcNameLen();
int findMinLenNum(int& s);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int N;
		cin >> N;
		nameList = vector<string>(N);
		nameLen = vector<int>(20001, 0);
		for (int i = 0; i < N; ++i) {
			string name;
			cin >> name;
			nameList[i] = name;
		}

		// proc
		sortName();
		cout << "#" << t + 1 << " " << endl;
		for (int i = 0; i < nameList.size(); ++i) {
			if (i + 1 < nameList.size() && nameList[i].compare(nameList[i + 1]) == 0) continue;
			cout << nameList[i] << endl;
		}

		// free
		nameList.clear();
	}
}

void sortName() {

	calcNameLen();
	int minLen = 0;
	int start = 0;

	while (1) {
		int nextStart = findMinLenNum(minLen);
		if (nextStart == MAX_NAME) break;
		radixSort(minLen, start);

		start += nextStart;
		++minLen;
	}
}

void radixSort(int len, int listStart) {
	vector<string> ret(nameList.size() - listStart);
	for (int i = len - 1; i >= 0; --i) {
		// 넣기
		for (int j = listStart; j < nameList.size(); ++j) {
			radix[(int)nameList[j][i] - 97].push(nameList[j]);
		}
		// 빼기
		int idx = 0;
		for (int j = 0; j < radix.size(); ++j) {
			while (!radix[j].empty()) {
				ret[idx] = radix[j].front();
				radix[j].pop();
				++idx;
			}
		}
	}

	// 옮기기
	for (int i = listStart; i < nameList.size(); ++i) {
		nameList[i] = ret[i - listStart];
	}
}

void calcNameLen() {
	for (int i = 0; i < nameList.size(); ++i) {
		++nameLen[nameList[i].size()];
	}
}

int findMinLenNum(int& s) {
	for (int i = s; i < 20001; ++i) {
		if (nameLen[i] > 0) {
			s = i;
			return nameLen[i];
		}
	}
	return 20001;
}