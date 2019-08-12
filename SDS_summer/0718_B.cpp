#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF	987654321

using namespace std;

struct Edge {
	int num;
	int cost;
	Edge(int _a, int _c) : num(_a), cost(_c) {}
	Edge() {}
};

struct numDk {
	int num;
	int dk;
	numDk(int n, int d) :num(n), dk(d) {}
	numDk() {}
};

struct comp {
	bool operator()(numDk a, numDk b) {
		return a.dk > b.dk;
	}
};

priority_queue<numDk, vector<numDk>, comp> min_q;

vector< vector<Edge> > adj;
vector<int> dk;
vector<bool> visited;

int min(int a, int b) { return a < b ? a : b; }

int main() {
	// input
	int V, E;
	cin >> V >> E;

	adj = vector< vector<Edge> >(V + 1, vector<Edge>());
	dk = vector<int>(V + 1, INF);
	visited = vector<bool>(V + 1, false);

	int start;
	scanf("%d", &start);
	for (int i = 0; i < E; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back(Edge(v, w));
	}

	// proc
	dk[start] = 0;
	min_q.push(numDk(start, dk[start]));

	while (!min_q.empty()) {
		numDk cur = min_q.top();
		min_q.pop();

		if (visited[cur.num]) continue;
		else visited[cur.num] = true;

		for (int i = 0; i < adj[cur.num].size(); ++i) {
			if (dk[adj[cur.num][i].num] > dk[cur.num] + adj[cur.num][i].cost) {
				dk[adj[cur.num][i].num] = dk[cur.num] + adj[cur.num][i].cost;
				min_q.push(numDk(adj[cur.num][i].num, dk[adj[cur.num][i].num]));
			}
		}
	}

	for (int i = 1; i < dk.size(); ++i) {
		if (dk[i] == INF) printf("INF\n");
		else printf("%d\n", dk[i]);
	}

	// free
	dk.clear();
	visited.clear();
	adj.clear();
}