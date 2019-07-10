#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>

#define MAX_STR		101

using namespace std;

int cache[MAX_STR][MAX_STR];
vector<string> result;
string wildCard, str;

bool matchingWildCard(int w_idx, int s_idx);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		cin >> wildCard;

		// proc
		int wordNum;
		scanf("%d", &wordNum);
		for (int i = 0; i < wordNum; ++i) {
			cin >> str;
			memset(cache, -1, sizeof(cache));
			if (matchingWildCard(0, 0)) result.push_back(str);
		}

		sort(result.begin(), result.end());

		// result print
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << endl;
		}

		// result free
		result.clear();

		// free
		str.clear();
		wildCard.clear();
	}

	
}

bool matchingWildCard(int w_idx, int s_idx) {

	int& ret = cache[w_idx][s_idx];
	if (ret != -1) return ret;

	// ���ϵ�ī�� ?�ų� ���� idx���� str�� ���� ���ڸ� ���� ��
	// ���� ����� �ݺ��� ����
	while (w_idx < wildCard.size() && s_idx < str.size() &&
		(wildCard[w_idx] == '?' || wildCard[w_idx] == str[s_idx])) {
		++w_idx;
		++s_idx;
	}

	// ���ϵ�ī�� ������ ���ߴµ� str�� �������� 1, ������������ 0
	if (w_idx == wildCard.size()) return ret = (s_idx == str.size());

	// * �� ������ ���
	if (wildCard[w_idx] == '*') {
		for (int skip = 0; s_idx + skip <= str.size(); ++skip) {
			if (matchingWildCard(w_idx + 1, s_idx + skip)) return ret = 1;
		}
	}
	return ret = 0;
}

// ó������ �̰� �� dp�ΰ� �;� ���Ҷ� �޸������̼��ϰ� �����Ҷ� �װ��� �Ѵٴ� �������� �����ϰ� ���� Ǯ��ϱ�
// ��Ǯ���� �������� �񱳹����� dp ������.
// �������� ���ߴ� ���� *�϶� ���� ���ڰ� ������ ù��° ���� str���� ã���� �ȴٰ� �����ߴµ�
// �̷����ϸ� paã�ƾ��Ҷ� ppa ������ ������ ����� ����Ž������ �ϳ��� ���غ��� �ȴٴ� ���� 
// �˰Եǰ� �׷��� dp�� ������ �� �ִٴ� ���� ���ݰ� ��....