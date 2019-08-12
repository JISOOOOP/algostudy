#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int v) : val(v), next(0) {}
	Node() {}
};

struct d_data {
	int num;
	int depth;
	d_data(int n, int d) : num(n), depth(d) {}
	d_data() {}
};

vector<Node*> adj;
vector<int> depth;
vector< vector<int> > cache;

int calcDepth();
void insert(int s, int e);
int calcCache(int k, int idx);

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int log2(int num) { return log(num) / log(2); }

int main() {
	// input
	int N;
	cin >> N;

	adj = vector<Node*>(N + 1, 0);
	depth = vector<int>(N + 1, 0);
	cache = vector< vector<int> >(20, vector<int>(N + 1, 0));
	for (int i = 1; i < N; ++i) {
		int _s, _e, s, e;
		scanf("%d %d", &_s, &_e);
		s = min(_s, _e);
		e = max(_s, _e);
		insert(s, e);
	}

	int maxDepth = calcDepth();
	cache[0][1] = 0;
	for (int i = 1; i <= N; ++i) {
		calcCache(log2(maxDepth), i);
	}

	int M;
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int _a, _b, a, b;
		scanf("%d %d", &_a, &_b);
		if (depth[_a] < depth[_b]) {
			a = _a;
			b = _b;
		}
		else if(depth[_a] > depth[_b]){
			a = _b;
			b = _a;
		}
		

	}
}

void findSameParent(int a, int b) {
	int depthDiff = depth[b] - depth[a];
	for (int i = 20; i >= 0; --i) {
		if(depthDiff )
	}
}

int calcCache(int k, int idx) {
	// base case
	if (k == 0) return cache[0][idx];

	// memoization
	int& ret = cache[k][idx];
	if (ret != 0) return ret;

	return ret = cache[k - 1][calcCache(k - 1, idx)];
}

int calcDepth() {
	queue<d_data> q;
	q.push(d_data(1, 0));

	int maxDepth = 0;
	while (!q.empty()) {
		d_data cur = q.front();
		q.pop();

		Node* cur_node = adj[cur.num];
		while (cur_node != 0) {
			depth[cur_node->val] = cur.depth + 1;
			if (maxDepth < depth[cur_node->val]) maxDepth = depth[cur_node->val];
			cache[0][cur_node->val] = cur.num;
			q.push(d_data(cur_node->val, cur.depth + 1));
			cur_node = cur_node->next;
		}
	}
	return maxDepth;
}

void insert(int s, int e) {
	Node* node = new Node(e);
	if (adj[s] == 0) adj[s] = node;
	else {
		Node* cur = adj[s];
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = node;
	}
}