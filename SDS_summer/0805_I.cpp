#include <iostream>
#include <memory.h>
#include <vector>

using namespace std;

typedef long long ll;

ll cache[21];
bool visited[21];

ll fact(int n);
void k_proc(int N, ll K, int& num);
ll findOrder(vector<int>& seq, int idx, int size, int& num);

int main() {
	int N;
	cin >> N;

	int order;
	cin >> order;

	memset(cache, -1, sizeof(cache));
	memset(visited, false, sizeof(visited));
	fact(20);
	int num = N;
	if (order == 1) {
		ll K;
		scanf("%lld", &K);
		k_proc(N, K, num);
	}
	else if (order == 2) {
		vector<int> seq(N + 1, 0);
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &seq[i]);
		}
		printf("%lld\n", findOrder(seq, 1, seq.size(), num));
	}

	return 0;
}

ll fact(int n) {
	if (n == 0) return 1;

	ll& ret = cache[n];
	if (ret != -1) return ret;

	return ret = n * fact(n - 1);
}

void k_proc(int N, ll K, int& num) {
	if (num == 0) return;
	ll temp = 0;
	ll curNum = fact(--num);
	for (int i = 1; i <= N; ++i) {
		if (!visited[i]) {
			temp += curNum;
			if (temp >= K) {
				cout << i << ' ';
				visited[i] = true;
				k_proc(N, K - (temp - curNum), num);
				return;
			}
		}
	}
}

ll findOrder(vector<int>& seq, int idx, int size, int& num) {
	if (num == 0) return 1;

	ll curNum = fact(--num);
	ll temp = 0;
	for (int i = 1; i < size; ++i) {
		if (!visited[i]) {
			if (seq[idx] == i) {
				visited[i] = true;
				return temp + findOrder(seq, idx + 1, size, num);
			}
			temp += curNum;
		}
	}
}