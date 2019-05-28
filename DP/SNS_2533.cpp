#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int init = 999999;

vector< set<int> > edge(1000001);
vector<bool> visited;
vector< vector<int> > cache;

bool isTerminal(int num);
int sns(int start, bool before);				// before 0 전단계 수행x

int main() {

	// input && init && alloc
	int N;
	cin >> N;

	for (int n = 0; n < N - 1; ++n) {
		int frnd1, frnd2;
		cin >> frnd1 >> frnd2;
		edge[frnd1].insert(frnd2);
		edge[frnd2].insert(frnd1);
	}

	for (int n = 0; n <= N; ++n) {
		visited.push_back(0);
	}

	for (int i = 0; i <= N; ++i) {
		vector<int> ele(3, -1);
		cache.push_back(ele);
	}

	// proc
	cout << sns(1, 1) << endl;

	// free
	edge.clear();
	visited.clear();
	cache.clear();
}

int sns(int start, bool before) {				// before 0 전단계 수행x
	// base case
	if (isTerminal(start)) return 1;

	// memoization
	int& ret = cache[start][before];
	if (ret != -1) return ret;

	ret = init;

	queue<int> child, grandChild;

	//visited[start] = 1;
	//// 자신과 연결 되있으면서 방문하지 않은 곳
	//// child
	//for (int i = 1; i < friends.size(); ++i) {
	//	if (friends[start][i] && !visited[i]) {
	//		visited[i] = 1;
	//		child.push(i);
	//		for (int j = 1; j < friends.size(); ++j) {
	//			if (friends[i][j] && !visited[j]) {
	//				grandChild.push(j);
	//			}
	//		}
	//		visited[i] = 0;
	//	}
	//}

	visited[start] = 1;
	set<int> temp = edge[start];
	while(!temp.empty()){
		int v = *(temp.begin());
		temp.erase(v);
		if (!visited[v]) {
			visited[v] = 1;
			child.push(v);
			set<int> temp_ = edge[v];
			while (!temp_.empty()) {
				int v_ = *(temp_.begin());
				temp_.erase(v_);
				if (!visited[v_]) grandChild.push(v_);
			}
			visited[v] = 0;
		}
	}

	// start 방문 o, child 방문 x, grandChild 방문
	int case1 = 1;
	while (!grandChild.empty()) {
		int next = grandChild.front();
		grandChild.pop();
		case1 += sns(next, 1);
	}
	if (ret > case1) ret = case1;

	if (before) {
		// start 방문 x, child 방문 o
		int case2 = 0;
		while (!child.empty()) {
			int next = child.front();
			child.pop();
			case2 += sns(next, 0);
		}
		if (ret > case2) ret = case2;
	}

	visited[start] = 0;

	return ret;
}

bool isTerminal(int num) {
	/*for (int i = 1; i < friends.size(); ++i) {
		if (friends[num][i] && !visited[i]) {
			return false;
		}
	}
	return true;*/

	set<int> temp = edge[num];
	while (!temp.empty()) {
		int v = *(temp.begin());
		temp.erase(v);
		if (!visited[v]) return false;
	}
	return true;
}