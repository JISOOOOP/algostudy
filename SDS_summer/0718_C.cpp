#include <iostream>
#include <vector>
#include <queue>

#define INF	987654321

using namespace std;

struct Edge {
	int start;
	int dst;
	int time;
	Edge(int s, int d, int t) : start(s), dst(d), time(t) {}
};

vector<int> dist;
vector<Edge> edge;

int main() {
	// input
	int N, M;
	cin >> N >> M;

	dist = vector<int>(N + 1, INF);
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		edge.push_back(Edge(a, b, c));
	}

	// proc
	dist[1] = 0;
	bool change = false;
	for (int v = 0; v <= N; ++v) {
		change = false;
		for (int i = 0; i < edge.size(); ++i) {
			int s = edge[i].start;
			int d = edge[i].dst;
			int t = edge[i].time;

			if (dist[s] == INF) continue;

			// update
			if (dist[d] > dist[s] + t) {
				change = true;
				dist[d] = dist[s] + t;
			}
		}
	}

	if (change) {
		printf("-1\n");
	}
	else {
		for (int i = 2; i < dist.size(); ++i) {
			if(dist[i] == INF) printf("-1\n");
			else printf("%d\n", dist[i]);
		}
	}

	// free
	edge.clear();
	dist.clear();
}