#include <iostream>
#include <vector>

using namespace std;

vector<int> sequence;
vector<int> cache;
vector<int> result;

int lis(int N);				// 부분 증가 순열 중 가장 긴 길이
int is(int start);			// start부터 시작하는 증가 순열의 길이
int max(int a, int b);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {

		// init && alloc
		int N;
		scanf("%d", &N);
		for (int n = 0; n < N; ++n) {
			int temp;
			scanf("%d", &temp);
			sequence.push_back(temp);
		}

		for (int n = 0; n <= N; ++n) {
			cache.push_back(-1);
		}

		// proc
		result.push_back(lis(N));

		// free
		sequence.clear();
		cache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int lis(int N) {			// 부분 증가 순열 중 가장 긴 길이
	int temp, ret = 0;
	for (int i = 0; i < N; ++i) {
		temp = is(i);
		if (ret < temp) ret = temp;
	}
	return ret;
}

int is(int start) {			// start부터 시작하는 증가 순열의 길이
	int& ret = cache[start];
	if (ret != -1) return ret;

	// base condition, 한자리는 무조건 길이 1
	ret = 1;

	// next가 마지막 + 1이거나 start 값보다 큰 값 만나면 
	for (int i = start + 1; i < sequence.size(); ++i) {
		if(sequence[i] > sequence[start]) ret = max(ret, 1 + is(i));
	}
	return ret;
}

int max(int a, int b) {
	return a > b ? a : b;
}


// 처음에는 다음 재귀로 들어가는 것을 start의 값보다 큰 첫번째 것만 해서 오답.
// 생각해보니 1 2 7 3 4 7 같은 경우에 오답을 발생.
// 재귀로 들어가는 것을 start + 1 부터 끝까지 모두 재귀로 들어가서 확인해야함.
// 중복 연산은 메모이제이션 처리