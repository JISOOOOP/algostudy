#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > connected;
vector<int> rst_q;

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N, D, P;
		scanf("%d %d %d", &N, &D, &P);

		for (int i = 0; i < N; ++i) {
			vector<int> ele;
			for (int j = 0; j < N; ++j) {
				int temp;
				scanf("%d", &temp);
				ele.push_back(temp);
			}
			connected.push_back(ele);
		}

		int q;
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {

		}

	}

}