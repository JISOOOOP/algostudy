#include <iostream>
#include <vector>
#include <string>

#define MAX_CASE		5
#define MAX_STACK		6
#define INF				9999

using namespace std;

vector< vector<int> >cache;
vector<int> LCache;
vector<int> pi;
vector<int> result;
string str;

const int caseLevel[MAX_CASE] = { 10, 1, 2, 4, 5 };

int pi_level();
int calcMinLevel(int start);						// minLevel ���
int calcMinTermLevel(int start, int term);			// �������� �ּ� ���̵�
int calcLevel(int start, int caseType);			// start���� caseType�� ���� ���ϱ�
int min(int a, int b);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {

		// input, init && alloc
		cin >> str;
		for (int i = 0; i < str.size(); ++i) {
			char buf;
			buf = str[i];
			pi.push_back(atoi(&buf));
		}

		for (int i = 0; i < str.size(); ++i) {
			vector<int> ele(MAX_CASE, -1);
			cache.push_back(ele);
			LCache.push_back(-1);
		}

		// proc
		result.push_back(pi_level());

		// free
		pi.clear();
		str.clear();
		cache.clear();
		LCache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int pi_level() {
	// 0~pi.size-1 ���� ��� caseType �� �غ���
	for (int i = 0; i < pi.size(); ++i) {
		for (int j = 1; j < MAX_CASE; ++j) {
			calcLevel(i, j);
		}
	}

	return calcMinLevel(0);
}

int calcMinLevel(int start) {						// minLevel ���

	// base case
	if (start == pi.size()) return 0;

	int& ret = LCache[start];
	if (ret != -1) return ret;

	ret = INF;

	for (int L = 3; L <= 5; ++L) {
		if (start + L <= pi.size())
			ret = min(ret, calcMinLevel(start + L) + calcMinTermLevel(start, L));
	}
	return ret;
}

int calcMinTermLevel(int start, int term) {			// �������� �ּ� ���̵�
	// 
	for (int i = 1; i < MAX_CASE; ++i) {
		if ((cache[start][i] % MAX_CASE) == (term % MAX_CASE)) return caseLevel[i];
	}
	return caseLevel[0];
}

int calcLevel(int start, int caseType) {			// start���� caseType�� ���� ���ϱ�

	int& ret = cache[start][caseType];
	if (ret != -1) return ret;

	// base case
	if (start + 1 == pi.size()) return ret = 1;

	// 1. ��� ���� ���� ��(1) 
	if (caseType == 1) {
		if (pi[start] == pi[start + 1]) return ret = 1 + calcLevel(start + 1, 1);
		return ret = 1;
	}
	// 2. ���� 1����(2)
	if (caseType == 2) {
		// ������ ���밪�� 1�� ���� ���ϸ� ���������� 4�� ���� ����
		if (abs(pi[start + 1] - pi[start]) != 1) return 1;
		if (start == 0) return ret = 1 + calcLevel(start + 1, 2);
		if (pi[start] - pi[start - 1] == pi[start + 1] - pi[start]) return ret = 1 + calcLevel(start + 1, 2);
		if (start + 2 == pi.size()) return ret = 1;
		if (pi[start + 1] - pi[start] == pi[start + 2] - pi[start + 1]) return ret = 2 + calcLevel(start + 2, 2);
		return ret = 1;
	}
	// 3,4 ���� �յڸ� ���⶧���� start == 0�̸� stack + 1�ϰ� ������
	// 3. ���� ������(4)
	if (caseType == 3) {
		if (start == 0) return ret = 1 + calcLevel(start + 1, 3);
		if (pi[start - 1] == pi[start + 1]) return ret = 1 + calcLevel(start + 1, 3);
		return ret = 1;
	}

	if (caseType == 4) {
		// 4case ����, start == 0 �̸� stack + 1
		// 2���� ��, 1. �յ����� = stack + 1, 2. �� �ڵ� ���� = stack + 2(�ڵڰ� ���� �ƴҰ��)
		// X 0 0 X ��Ȳ�� 3���� �̸��̱� ������ ������ �� ����
		if (start == 0) return ret = 1 + calcLevel(start + 1, 4);
		if (pi[start] - pi[start - 1] == pi[start + 1] - pi[start]) return ret = 1 + calcLevel(start + 1, 4);
		if (start + 2 == pi.size()) return ret = 1;
		if (pi[start + 1] - pi[start] == pi[start + 2] - pi[start + 1]) return ret = 2 + calcLevel(start + 2, 4);
		return ret = 1;
	}
}

int min(int a, int b) {
	return a > b ? b : a;
}


// �̹� ������ �ؼ��� �������� �޸������̼� �ϴ� ����� �߸����.
// ���� ������ ����� �� �ڸ����� case�� ���� stack�� ������̴� ���� �޸������̼� �Ͽ��µ�,
// ���������� �� �޸��� ���̼� �� �ǹ̴� ���� �� ���� �� �ڸ����� �����Ҷ� �ּ� ���̵���
// �޸������̼� ���־�� �ߴ�.
// ���� ���ɴ� ������ ��� ���� �Ϻ� �ȸ´� ���� �־ ���� �ٽ� Ȯ���� �ʿ� ����.