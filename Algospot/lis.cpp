#include <iostream>
#include <vector>

using namespace std;

vector<int> sequence;
vector<int> cache;
vector<int> result;

int lis(int N);				// �κ� ���� ���� �� ���� �� ����
int is(int start);			// start���� �����ϴ� ���� ������ ����
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

int lis(int N) {			// �κ� ���� ���� �� ���� �� ����
	int temp, ret = 0;
	for (int i = 0; i < N; ++i) {
		temp = is(i);
		if (ret < temp) ret = temp;
	}
	return ret;
}

int is(int start) {			// start���� �����ϴ� ���� ������ ����
	int& ret = cache[start];
	if (ret != -1) return ret;

	// base condition, ���ڸ��� ������ ���� 1
	ret = 1;

	// next�� ������ + 1�̰ų� start ������ ū �� ������ 
	for (int i = start + 1; i < sequence.size(); ++i) {
		if(sequence[i] > sequence[start]) ret = max(ret, 1 + is(i));
	}
	return ret;
}

int max(int a, int b) {
	return a > b ? a : b;
}


// ó������ ���� ��ͷ� ���� ���� start�� ������ ū ù��° �͸� �ؼ� ����.
// �����غ��� 1 2 7 3 4 7 ���� ��쿡 ������ �߻�.
// ��ͷ� ���� ���� start + 1 ���� ������ ��� ��ͷ� ���� Ȯ���ؾ���.
// �ߺ� ������ �޸������̼� ó��