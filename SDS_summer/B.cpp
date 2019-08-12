#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int val;
	Node* next;
	Node(int v) : val(v), next(0) {}
};

vector<Node*> adj;
vector<int> front;

void calcFront();
int findFirst();
void modifyFront(int idx);
void insert(int a, int b);

int main() {
	// input
	int N, M;
	cin >> N >> M;

	front = vector<int>(N + 1, 0);
	adj = vector<Node*>(N + 1, 0);
	for (int i = 0; i < M; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		insert(a, b);
	}

	calcFront();
	for (int i = 0; i < N; ++i) {
		int first = findFirst();
		printf("%d ", first);
		modifyFront(first);
	}
	printf("\n");
}

void insert(int a, int b) {
	Node* node = new Node(b);
	if (adj[a] == 0) adj[a] = node;
	else {
		Node* cur = adj[a];
		while (cur->next != 0) {
			cur = cur->next;
		}
		cur->next = node;
	}
}

void calcFront() {
	for (int i = 1; i < front.size(); ++i) {
		if (adj[i] != 0) {
			int cnt = 0;
			Node* cur = adj[i];
			while (cur != 0) {
				++front[cur->val];
				cur = cur->next;
			}
		}
	}
}

int findFirst() {
	for (int i = 1; i < front.size(); ++i) {
		if (front[i] == 0) return i;
	}
}

void modifyFront(int idx) {
	Node* cur = adj[idx];
	while (cur != 0) {
		--front[cur->val];
		cur = cur->next;
	}
	front[idx] = -1;
}
