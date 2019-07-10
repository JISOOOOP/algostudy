#include <iostream>
#include <vector>

using namespace std;

int dayCost[1000001] = { 0, };
int cache[1000001][]

int million(vector<int>& dayCost, int day, int coin, vector< vector<int> >& cache);
int max(int a, int b);

int main() {

	int T;
	cin >> T;
	vector<int> result(T, 0);

	for (int t = 0; t < T; ++t) {
		int N;
		cin >> N;

		// input
		vector< vector<int> > cache;
		for (int n = 0; n < N; ++n) {
			vector<int> ele(N + 1, -1);
			cache.push_back(ele);
		}

		for (int n = 0; n < N; ++n) {
			scanf("%d", &dayCost[n]);
		}

		// proc
		result[t] = million(dayCost, 0, 0, cache);

		// free
		for (int i = 0; i <= N; ++i) {
			dayCost[i] = 0;
		}
		cache.clear();
	}
	// result print
	for (int t = 0; t < T; ++t) {
		cout << "#" << t + 1 << ' ' << result[t] << endl;
	}

}

int million(vector<int>& dayCost, int day, int coin, vector< vector<int> >& cache) {
	// base case
	if (day == dayCost.size() - 1) return 0;
	
	// memoization
	int& ret = cache[day][coin];
	if (ret != -1) return ret;

	ret = 0;

	// all sale
	if(coin > 0) ret = max(ret, coin * dayCost[day] + million(dayCost, day + 1, 0, cache));
	// buy, nothing
	ret = max(ret, million(dayCost, day + 1, coin + 1, cache) - dayCost[day]);
	ret = max(ret, million(dayCost, day + 1, coin, cache));

	return ret;
}

int max(int a, int b) {
	return a > b ? a : b;
}