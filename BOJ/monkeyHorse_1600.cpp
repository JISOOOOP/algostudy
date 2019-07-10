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

		// cur�� �� ���� �ڸ��� �׶��� mcnt ���
		if (cur.r == size_r - 1 && cur.c == size_c - 1) return cur.mcnt;
		// world ���̰ų� ��ֹ� ������ �ѱ��
		// �� ������ K�� ����ϰ� �����ڸ� ������ ������ �ѱ��
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

		// K�� �� ���������� ����x
		if (cur.k >= K) continue;
		for (int i = 0; i < 8; ++i) {
			next.r = cur.r + dr_h[i];
			next.c = cur.c + dc_h[i];
			next.k = cur.k + 1;
			next.mcnt = cur.mcnt + 1;
			nextDist.push(next);
		}
	}
	// ť�� ��������� ��ǥ�� �������� ���� ���
	return -1;
}


// ó������ ���� ������ K���� �����̰� ������ ���������� �����̴� �� �����ϰ� ������ Ǯ����.
// �ݷʷ� K�� ���� ���� ���� �� ������ �� ������ ���������� �� �� �־ 0~K������ ���� ��������
// ������ ���������� ���� ������� �����Ͽ���. 
// ������ �ٸ� �ݷʷ� ��ֹ��� ���� ������ �������� ���� �������� �� �ؾ��ϴ� ��Ȳ�� ����.
// �׷��� �� ������ ������ �����Ӱ� ���� ������ ��� ť�� push�ϰ� ���ܻ�Ȳ ��� �����ϴ� ������� ����