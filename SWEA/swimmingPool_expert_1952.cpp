#include <iostream>
#include <vector>

using namespace std;

vector<int> price(4, 0), month(12, 0);
vector<int> cache(12, -1);

int swimmingPool(int m);

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		for (int i = 0; i < 4; ++i) {
			cin >> price[i];
		}

		for (int i = 0; i < 12; ++i) {
			cin >> month[i];
		}

		// proc
		result[t] = swimmingPool(0);

		// free
		for (int i = 0; i < 12; ++i) {
			cache[i] = -1;
		}
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int swimmingPool(int m) {
	// base case
	if (m >= 12) return 0;

	// memoization
	int& ret = cache[m];
	if (ret != -1) return ret;

	ret = 10000000;

	if (month[m] == 0) return ret = swimmingPool(m + 1);

	int temp = 0;
	// 1 day
	temp = (price[0] * month[m]) + swimmingPool(m + 1);
	if (ret > temp) ret = temp;

	// 1 month
	temp = price[1] + swimmingPool(m + 1);
	if (ret > temp) ret = temp;

	// 3 month
	temp = price[2] + swimmingPool(m + 3);
	if (ret > temp) ret = temp;

	// 1 year
	temp = price[3];
	if (ret > temp) ret = temp;

	return ret;
}

