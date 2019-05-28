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
int calcMinLevel(int start);						// minLevel 계산
int calcMinTermLevel(int start, int term);			// 구간에서 최소 난이도
int calcLevel(int start, int caseType);			// start에서 caseType의 스택 구하기
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
	// 0~pi.size-1 까지 모든 caseType 다 해보기
	for (int i = 0; i < pi.size(); ++i) {
		for (int j = 1; j < MAX_CASE; ++j) {
			calcLevel(i, j);
		}
	}

	return calcMinLevel(0);
}

int calcMinLevel(int start) {						// minLevel 계산

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

int calcMinTermLevel(int start, int term) {			// 구간에서 최소 난이도
	// 
	for (int i = 1; i < MAX_CASE; ++i) {
		if ((cache[start][i] % MAX_CASE) == (term % MAX_CASE)) return caseLevel[i];
	}
	return caseLevel[0];
}

int calcLevel(int start, int caseType) {			// start에서 caseType의 스택 구하기

	int& ret = cache[start][caseType];
	if (ret != -1) return ret;

	// base case
	if (start + 1 == pi.size()) return ret = 1;

	// 1. 모든 숫자 같을 때(1) 
	if (caseType == 1) {
		if (pi[start] == pi[start + 1]) return ret = 1 + calcLevel(start + 1, 1);
		return ret = 1;
	}
	// 2. 단조 1증감(2)
	if (caseType == 2) {
		// 차이의 절대값이 1인 점만 비교하면 나머지것은 4번 경우과 동일
		if (abs(pi[start + 1] - pi[start]) != 1) return 1;
		if (start == 0) return ret = 1 + calcLevel(start + 1, 2);
		if (pi[start] - pi[start - 1] == pi[start + 1] - pi[start]) return ret = 1 + calcLevel(start + 1, 2);
		if (start + 2 == pi.size()) return ret = 1;
		if (pi[start + 1] - pi[start] == pi[start + 2] - pi[start + 1]) return ret = 2 + calcLevel(start + 2, 2);
		return ret = 1;
	}
	// 3,4 번은 앞뒤를 보기때문에 start == 0이면 stack + 1하고 다음비교
	// 3. 숫자 번갈아(4)
	if (caseType == 3) {
		if (start == 0) return ret = 1 + calcLevel(start + 1, 3);
		if (pi[start - 1] == pi[start + 1]) return ret = 1 + calcLevel(start + 1, 3);
		return ret = 1;
	}

	if (caseType == 4) {
		// 4case 예외, start == 0 이면 stack + 1
		// 2가지 비교, 1. 앞뒤차이 = stack + 1, 2. 뒤 뒤뒤 차이 = stack + 2(뒤뒤가 끝이 아닐경우)
		// X 0 0 X 상황은 3스택 미만이기 때문에 무시할 수 있음
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


// 이번 문제는 해설과 비교했을때 메모이제이션 하는 대상이 잘못됬다.
// 내가 구현한 방식은 각 자리에서 case에 따라 stack이 몇번쌓이는 지를 메모이제이션 하였는데,
// 실질적으로 이 메모이 제이션 한 의미는 없는 것 같고 각 자리에서 시작할때 최소 난이도를
// 메모이제이션 해주어야 했다.
// 예제 테케는 맞지만 댓글 테케 일부 안맞는 것이 있어서 조건 다시 확인할 필요 있음.