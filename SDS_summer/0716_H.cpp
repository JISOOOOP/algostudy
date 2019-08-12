#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> idxTree;

int main() {
	// input
	int N;
	cin >> N;

	int x = -1;
	while (pow(2, ++x) > 1000001);
	idxTree = vector<int>(pow(2, x) * 2, 0);
	int idxStart = pow(2, x);

	for (int i = 0; i < N; ++i) {
		int order;
		scanf("%d", &order);
		if (order == 1) {
			int num;
			scanf("%d", &num);
		}
		else if (order == 2) {
			int taste, num;
			scanf("%d %d", &taste, &num);
			modify(idxStart + taste - 1, num - idxTree[idxStart + taste - 1]);
		}
	}
}

int drawNum(int s, int e) {

}

void modify(int idx, int diff) {
	// base case
	if (idx == 0) return;

	idxTree[idx] += diff;
	modify(idx / 2, diff);
}