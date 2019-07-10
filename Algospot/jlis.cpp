#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > cache;
vector<long long> seq1, seq2;
vector<int> result;

int jlis();				// seq1_start = 0~seq1.size()-1 , seq2_start = 0~seq2.size()-1 다 해보기
int combineIs(int seq1_start, int seq2_start);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		int N, M;
		scanf("%d %d", &N, &M);

		// init && alloc
		for (int n = 0; n < N; ++n) {
			long long temp;
			scanf("%d", &temp);
			seq1.push_back(temp);
		}

		for (int m = 0; m < M; ++m) {
			long long temp;
			scanf("%d", &temp);
			seq2.push_back(temp);
		}

		for (int n = 0; n <= N; ++n) {
			vector<int> ele(M + 1, -1);
			cache.push_back(ele);
		}

		// proc
		result.push_back(jlis());

		// free
		seq1.clear();
		seq2.clear();
		cache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int jlis() {				// seq1_start = 0~seq1.size()-1 , seq2_start = 0~seq2.size()-1 다 해보기
	int ret = -1;

	for (int i = 0; i < seq1.size(); ++i) {
		for (int j = 0; j < seq2.size(); ++j) {
			int temp = combineIs(i, j);
			ret = (ret > temp) ? ret : temp;
		}
	}
	return ret;
}

int combineIs(int seq1_start, int seq2_start) {
	// Memoization
	int& ret = cache[seq1_start][seq2_start];
	if (ret != -1) return ret;

	ret = 1;

	// base case
	// 1. 둘 다 끝까지 확인했으면
	if (seq1_start == seq1.size() && seq2_start == seq2.size()) return ret = 0;

	// 둘 중 작은 쪽 선택 
	// 작은 쪽 수열 중 seq_start보다 큰 값 idx = seq_start + skip 으로 재귀
	int skip = 0;
	if (seq1_start != seq1.size() && (seq2_start == seq2.size() || seq1[seq1_start] < seq2[seq2_start])) {
		while (seq1_start + ++skip < seq1.size() && seq1[seq1_start] >= seq1[seq1_start + skip]);
		return ret += combineIs(seq1_start + skip, seq2_start);
	}
	// 반대 조건
	else if (seq2_start != seq2.size() && (seq1_start == seq1.size() || seq1[seq1_start] > seq2[seq2_start])) {
		while (seq2_start + ++skip < seq2.size() && seq2[seq2_start] >= seq2[seq2_start + skip]);
		return ret += combineIs(seq1_start, seq2_start + skip);
	}
	// 예외처리, 둘이 같은 값이면 아무거나 하나 버림
	else if (seq1[seq1_start] == seq2[seq2_start]) return ret = combineIs(seq1_start + 1, seq2_start);

}


// 흠.. 뭐가 오답일까... 알고스팟 오답뜸.. 공개 테케 및 답글 테케는 통과
// 구현 과정은 완탐으로 구현 후 메모이제이션 적용하는 방식으로 구현
// 시작점을 고정으로 잡고 최장길이 구하는 과정을 모든 시작점의 경우에 시도
// 그 중 가장 큰 값을 출력
// 입력값 long long 바꿨는데도 오답.. 뭘까..