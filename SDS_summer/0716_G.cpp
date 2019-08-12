#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;

	Node(int v) : val(v), left(0), right(0) {}

	void insert(int v) {
		if (v < val) {
			if (left) {
				left->insert(v);
			}
			else {
				Node* node = new Node(v);
				left = node;
			}
		}
		else {
			if (right) {
				right->insert(v);
			}
			else {
				Node* node = new Node(v);
				right = node;
			}
		}
	}
};

vector<int> input;

void proc();
Node* makeTree();
void post_order(Node* root);

int main() {
	// input
	int x = 0;
	while (cin >> x) {
		input.push_back(x);
	}

	// proc
	proc();

	// free
	input.clear();
}

void proc() {
	Node* root = makeTree();
	post_order(root);
}

Node* makeTree() {
	Node* root = new Node(input[0]);
	for (int i = 1; i < input.size(); ++i) {
		root->insert(input[i]);
	}
	return root;
}

void post_order(Node* root) {
	// base case
	if (root == 0) return;

	post_order(root->left);
	post_order(root->right);
	cout << root->val << endl;
}