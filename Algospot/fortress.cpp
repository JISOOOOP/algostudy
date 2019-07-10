#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

struct TreeNode {
	vector<TreeNode*> children;
};

int x[101], y[101], r[101];
vector<int> result;

int solve(TreeNode* root);
int height(TreeNode* root, int& longest);
TreeNode* getTree(int root, int size);
bool isChild(int parent, int child, int size);
bool enclosed(int a, int b);
int calcDist(int x1, int y1, int x2, int y2);
int max(int a, int b);

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;

		// init
		memset(x, 0, sizeof(x));
		memset(y, 0, sizeof(y));
		memset(r, 0, sizeof(r));

		for (int i = 0; i < N; ++i) {
			cin >> x[i] >> y[i] >> r[i];
		}

		// make tree
		TreeNode tree;
		for (int i = 0; i < N; ++i) {
			tree.children.push_back(getTree(i, N));
		}

		// proc
		int longest = 0;
		for (int i = 0; i < tree.children.size(); ++i) {
			longest = max(longest, solve(tree.children[i]));
		}
		result.push_back(longest);
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

// solve
int solve(TreeNode* root) {

	int longest = 0;

	int h = height(root, longest);
	return max(longest, h);
}

// root�� �ֻ��� ��Ʈ�� ���� Ʈ���� ����
int height(TreeNode* root, int& longest) {
	// child�� root�� ���� Ʈ���� ���� ����
	vector<int> heights;
	for (int i = 0; i < root->children.size(); ++i) {
		heights.push_back(height(root->children[i], longest));
	}
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	// leaf - leaf ���µ� root ���� ���� ��� �� ���� �� ��
	if (heights.size() >= 2) {
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	}
	return heights.back() + 1;
}

// root�� root�� �ϴ� tree ����
TreeNode* getTree(int root, int size) {
	TreeNode* ret = new TreeNode();
	for (int i = 0; i < size; ++i) {
		if (isChild(root, i, size)) {
			ret->children.push_back(getTree(i, size));
		}
	}
	return ret;
}

// �������� �ڽ��̳�
bool isChild(int parent, int child, int size) {
	if (!enclosed(parent, child)) return false;
	for (int i = 0; i < size; ++i) {
		if (i != parent && i != child && enclosed(parent, i) && enclosed(i, child)) return false;
	}
	return true;
}

// a�� b�� �����ϳ�
bool enclosed(int a, int b) {
	return r[a] > r[b] && calcDist(x[a], y[a], x[b], y[b]) < (r[a] * r[a]);
}

// �� �� ���� �Ÿ�
int calcDist(int x1, int y1, int x2, int y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int max(int a, int b) {
	return a > b ? a : b;
}