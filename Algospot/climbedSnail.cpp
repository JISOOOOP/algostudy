#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > cache;
vector<int> result;

int climbedSnail(int day, int climbed, int M, int N);

int main() {

	// input && init && alloc
	int M, N;
	scanf("%d %d", &M, &N);

	for (int m = 0; m <= M; ++m) {
		vector<int> ele(N + 1, -1);
		cache.push_back(ele);
	}

	// proc
	result.push_back(climbedSnail(0, 0, M, N));

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int climbedSnail(int day, int climbed, int M, int N) {
	// base case
	if (day == M) climbed >= N ? 1 : 0;

	int& ret = cache[day][climbed];
	if (ret != -1) return ret;
	ret = 0;

	return ret = climbedSnail(day + 1, climbed + 1, M, N) + climbedSnail(day + 1, climbed + 2, M, N);

}