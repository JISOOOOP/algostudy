#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_T_P = 1000001;

vector<int> calcPi_KMP(string str);
vector<int> searchStr_KMP(string src, string dest, vector<int>& pi);

int main() {

	string T, P;
	getline(cin, T);
	getline(cin, P);

	vector<int> pi = calcPi_KMP(P);
	vector<int> result = searchStr_KMP(T, P, pi);

	cout << result.size() << endl;
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << ' ';
	}

	// free
	pi.clear();
	result.clear();

}

vector<int> calcPi_KMP(string str) {

	vector<int> pi(str.size() + 1, 0);

	// begin = �񱳸� ������ ��ġ
	// matched = �� �� ���� ����
	int begin = 1, matched = 0;

	while (begin + matched < str.size()) {
		if (str[matched] == str[begin + matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}

vector<int> searchStr_KMP(string src, string dest, vector<int>& pi) {

	vector<int> index;

	int begin = 0, matched = 0;

	while (begin + matched < src.size()) {
		if (src[begin + matched] == dest[matched]) {
			++matched;
			if (matched == dest.size()) {
				index.push_back(begin + 1);
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
		else {
			if (matched == 0) ++begin;
			else {
				// KMP
				// ��ã���� ��� pi Ȱ���Ͽ� begin ��ġ ����
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return index;
}