#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int num;
	Node* next;
	Node(int n) : num(n), next(0) {}
	Node() {}
};

vector<Node*> adj;
vector<bool> visited;
vector<int> numOrder, low;

int calcOrder(int num, int& order, int& CutNum, vector<int>& cut_p);
void insert(int a, int b);

int min(int a, int b) { return a < b ? a : b; }

int main() {
	// input
	int V, E;
	cin >> V >> E;

	adj = vector<Node*>(V + 1);
	visited = vector<bool>(V + 1, false);
	numOrder = vector<int>(V + 1, 0);
	low = vector<int>(V + 1, 0);
	for (int i = 0; i < E; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		insert(a, b);
		insert(b, a);
	}

	// proc
	int start = 1;
	int cutNum = 0;
	vector<int> cut_p;
	calcOrder(1, start, cutNum, cut_p);

	printf("%d\n", cutNum);
	for (int i = 0; i < cutNum; ++i) {
		printf("%d ", cut_p[i]);
	}
	cout << endl;

	// free
	adj.clear();
	visited.clear();
	numOrder.clear();
}

int calcOrder(int num, int& order, int& cutNum, vector<int>& cut_p) {
	// base case
	if (order == adj.size()) return 987654321;

	int low = order;
	int child = 0;

	numOrder[num] = order;
	visited[num] = true;
	Node* cur = adj[num];
	while (cur != 0) {
		int next = cur->num;
		if (!visited[next]) {
			++child;
			low = min(low, calcOrder(next, ++order, cutNum, cut_p));
		}
		else low = min(numOrder[next], low);
		cur = cur->next;
	}
	if (num != 1 && low >= numOrder[num]) {
		++cutNum;
		cut_p.push_back(num);
	}

	// root
	if (num == 1 && child >= 2) {
		++cutNum;
		cut_p.push_back(num);
	}
	return low;
}

void insert(int a, int b) {
	Node* node = new Node(b);
	if (adj[a] == 0) adj[a] = node;
	else {
		Node* cur = adj[a];
		while (cur->next != 0) cur = cur->next;
		cur->next = node;
	}
}