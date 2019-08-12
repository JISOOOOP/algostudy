#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct com {
	int s;
	int e;
	int cost;

	com(int a, int b, int c) : s(a), e(b), cost(c) {}
	com() {}
};

vector<int> uf;
vector<com> edge;

void uf_init();
void uf_union(int a, int b);
int uf_find(int a);

int main() {
	// input
	int N, M;
	cin >> N >> M;

	uf = vector<int>(N + 1, 0);
	edge = vector<com>(M);
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		edge[i] = com(a, b, c);
	}

	int ret = 0;

	sort(edge.begin(), edge.end(), [](com a, com b) -> bool {return a.cost < b.cost; });
	uf_init();
	for (int i = 0; i < M; ++i) {
		if (uf[edge[i].s] == uf[edge[i].e]) continue;
		uf_union(edge[i].s, edge[i].e);
		ret += edge[i].cost;
	}

	cout << ret << endl;

	// free
	uf.clear();
	edge.clear();
}

void uf_init() {
	for (int i = 0; i < uf.size(); ++i) {
		uf[i] = i;
	}
}

void uf_union(int a, int b) {
	int aRoot = uf_find(a);
	int bRoot = uf_find(b);
	uf[bRoot] = aRoot;
	for (int i = 1; i < uf.size(); ++i) {
		if (uf[i] == bRoot) uf[i] = aRoot;
	}
}

int uf_find(int a) {
	if (uf[a] == a) return a;
	return uf[a] = uf_find(uf[a]);
}