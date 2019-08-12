#include <iostream>
#include <vector>

#define INF	987654321

using namespace std;

vector< vector<int> > dist;

void fw_init();

int min(int a, int b) { return a < b ? a : b; }

int main() {
	// input
	int N, M;
	cin >> N >> M;

	dist = vector< vector<int> >(N + 1, vector<int>(N + 1, INF));
	fw_init();
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		dist[a][b] = min(dist[a][b], c);
	}

	// proc
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if(dist[i][j] == INF) printf("0 ", dist[i][j]);
			else printf("%d ", dist[i][j]);
		}
		printf("\n");
	}

}

void fw_init() {
	for (int i = 0; i < dist.size(); ++i) {
		dist[i][i] = 0;
	}
}