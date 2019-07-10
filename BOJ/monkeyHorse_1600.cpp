#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct point {
	int r;
	int c;
	int k;
	int mcnt;
};

const int dr_h[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dc_h[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
const int dr_m[4] = { 0, -1, 0, 1 };
const int dc_m[4] = { -1, 0, 1, 0 };

vector< vector<int> > world;
vector< vector< vector<int> > > visited;
vector<int> result;

queue<point> nextDist;

int minMoving_BFS(int K);

int main() {

	int K;
	scanf("%d", &K);

	int W, H;
	scanf("%d %d", &W, &H);

	// init && alloc
	for (int h = 0; h < H; ++h) {
		vector<int> ele;
		for (int w = 0; w < W; ++w) {
			int temp;
			scanf("%d", &temp);
			ele.push_back(temp);
		}
		world.push_back(ele);
	}

	for (int h = 0; h < H; ++h) {
		vector< vector<int> > ele_w;
		for (int w = 0; w < W; ++w) {
			vector<int> ele_k;
			for (int k = 0; k < K + 1; ++k) {
				ele_k.push_back(0);
			}
			ele_w.push_back(ele_k);
		}
		visited.push_back(ele_w);
	}

	// proc
	result.push_back(minMoving_BFS(K));

	// free
	world.clear();
	visited.clear();

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int minMoving_BFS(int K) {

	int size_r = world.size(), size_c = world[0].size();

	point start;
	start.c = start.r = start.k = start.mcnt = 0;
	nextDist.push(start);

	while (!nextDist.empty()) {
		point cur = nextDist.front();
		nextDist.pop();

		// cur이 맨 우하 자리면 그때의 mcnt 출력
		if (cur.r == size_r - 1 && cur.c == size_c - 1) return cur.mcnt;
		// world 밖이거나 장애물 있으면 넘기기
		// 말 움직임 K번 사용하고 현재자리 온적이 있으면 넘기기
		if (cur.r < 0 || cur.r >= size_r || cur.c < 0 || cur.c >= size_c) continue;
		if (world[cur.r][cur.c]) continue;
		if (visited[cur.r][cur.c][cur.k]) continue;

		visited[cur.r][cur.c][cur.k] = 1;

		point next;
		for (int i = 0; i < 4; ++i) {
			next.r = cur.r + dr_m[i];
			next.c = cur.c + dc_m[i];
			next.k = cur.k;
			next.mcnt = cur.mcnt + 1;
			nextDist.push(next);
		}

		// K번 다 움직였으면 동작x
		if (cur.k >= K) continue;
		for (int i = 0; i < 8; ++i) {
			next.r = cur.r + dr_h[i];
			next.c = cur.c + dc_h[i];
			next.k = cur.k + 1;
			next.mcnt = cur.mcnt + 1;
			nextDist.push(next);
		}
	}
	// 큐가 비었음에도 목표에 도달하지 못할 경우
	return -1;
}


// 처음에는 말의 움직임 K번을 움직이고 원숭이 움직임으로 움직이는 줄 이해하고 문제를 풀었다.
// 반례로 K번 보다 작은 수의 말 움직임 후 원숭이 움직임으로 갈 수 있어서 0~K번까지 먼저 움직인후
// 원숭이 움직임으로 가는 방법으로 구현하였다. 
// 하지만 다른 반례로 장애물에 의해 원숭이 움직임후 말의 움직임을 꼭 해야하는 상황이 생김.
// 그래서 한 점에서 원숭이 움직임과 말의 움직임 모두 큐에 push하고 제외상황 모두 제거하는 방식으로 구현