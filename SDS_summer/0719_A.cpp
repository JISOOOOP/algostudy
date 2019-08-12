#include <iostream>

using namespace std;

int gcd(int a, int b);

int main() {
	// input
	int a_b, a_t, b_b, b_t;
	cin >> a_t >> a_b;
	cin >> b_t >> b_b;

	// proc
	int s_a_b = a_b * b_b;
	int s_a_t = a_t * b_b;

	int s_b_b = b_b * a_b;
	int s_b_t = b_t * a_b;

	int r_b = s_a_b;
	int r_t = s_a_t + s_b_t;

	int ab_gcd = gcd(r_b, r_t);
	r_t /= ab_gcd;
	r_b /= ab_gcd;

	cout << r_t << ' ' << r_b << endl;
}

int gcd(int a, int b) {
	// base case
	if (a % b == 0) return b;
	return gcd(b, a%b);
}