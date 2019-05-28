#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1001;

vector< vector<float> > cache;
vector<float> result;

float climbedSnail(int day, int climbed, int M, int N);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int M, N;
		scanf("%d %d", &M, &N);

		for (int m = 0; m <= M; ++m) {
			vector<float> ele(MAX_N, -1);
			cache.push_back(ele);
		}

		// proc
		result.push_back(climbedSnail(0, 0, M, N));

		// cache free
		cache.clear();
	}
	// result print
	for (int i = 0; i < result.size(); i++) {
		printf("%.10lf\n", result[i]);
	}

	// result free
	result.clear();
}

float climbedSnail(int day, int climbed, int M, int N) {
	// base case
	if (day == M) return climbed >= N ? 1.0 : 0.0;

	float& ret = cache[day][climbed];
	if (ret != -1) return ret;
	ret = 0;

	return ret = 0.75 * climbedSnail(day + 1, climbed + 1, M, N) + 0.25 * climbedSnail(day + 1, climbed + 2, M, N);

}