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

	// 와일드카드 ?거나 같은 idx에서 str과 같은 문자면 다음 비교
	// 영역 벗어나면 반복문 종료
	while (w_idx < wildCard.size() && s_idx < str.size() &&
		(wildCard[w_idx] == '?' || wildCard[w_idx] == str[s_idx])) {
		++w_idx;
		++s_idx;
	}

	// 와일드카드 끝까지 비교했는데 str도 끝났으면 1, 아직남았으면 0
	if (w_idx == wildCard.size()) return ret = (s_idx == str.size());

	// * 을 만났을 경우
	if (wildCard[w_idx] == '*') {
		for (int skip = 0; s_idx + skip <= str.size(); ++skip) {
			if (matchingWildCard(w_idx + 1, s_idx + skip)) return ret = 1;
		}
	}
	return ret = 0;
}

// 처음에는 이게 왜 dp인가 싶어 비교할때 메모이제이션하고 소팅할때 그것을 한다는 방향으로 생각하고 문제 풀라니깐
// 안풀려서 답지보니 비교문에서 dp 적용함.
// 생각하지 못했던 점은 *일때 다음 문자가 나오는 첫번째 것을 str에서 찾으면 된다고 생각했는데
// 이렇게하면 pa찾아야할때 ppa 만나면 에러를 띄워서 완전탐색으로 하나씩 다해봐야 된다는 것을 
// 알게되고 그러면 dp를 적용할 수 있다는 점을 깨닫게 됨....