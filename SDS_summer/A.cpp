#include <iostream>
#include <vector>

using namespace std;

vector<int> uf;

void uf_init();
int uf_find(int a);
void uf_union(int a, int b);
bool isConnected(int a, int b);

int main() {
	// input
	int N, M;
	cin >> N >> M;

	uf = vector<int>(N + 1, 0);
	uf_init();
	for (int i = 0; i < M; ++i) {
		int order, a, b;
		scanf("%d %d %d", &order, &a, &b);
		if (order == 0) {
			uf_union(a, b);
		}
		else if (order == 1) {
			if (isConnected(a, b)) printf("YES\n");
			else printf("NO\n");
		}
	}

	// free
	uf.clear();
}

void uf_init() {
	for (int i = 0; i < uf.size(); ++i) {
		uf[i] = i;
	}
}

int uf_find(int a) {
	// base case
	if (uf[a] == a) return a;
	else return uf[a] = uf_find(uf[a]);
}

void uf_union(int a, int b) {
	int aRoot = uf_find(a);
	int bRoot = uf_find(b);
	uf[aRoot] = bRoot;
}

bool isConnected(int a, int b) {
	int aRoot = uf_find(a);
	int bRoot = uf_find(b);
	return aRoot == bRoot ? true : false;
}