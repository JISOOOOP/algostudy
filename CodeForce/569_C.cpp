#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll maxf(ll a, ll b);

int main() {
	// input
	ll N, Q;
	cin >> N >> Q;

	vector<ll> arr(N), max(N), sort(N);

	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}

	max[0] = arr[0];
	for (int i = 1; i < N; ++i) {
		max[i] = maxf(max[i - 1], arr[i]);
		if (max[i - 1] < arr[i]) sort[i - 1] = max[i - 1];
		else sort[i - 1] = arr[i];
	}

	for (int i = 0; i < Q; ++i) {
		ll temp;
		cin >> temp;
		if (temp < N) {
			cout << max[temp - 1] << " " << arr[temp] << endl;
		}
		else {
			cout << max[N - 1] << " " << sort[(temp - 1) % (N - 1)] << endl;
		}
	}

}

ll maxf(ll a, ll b) {
	return a > b ? a : b;
}