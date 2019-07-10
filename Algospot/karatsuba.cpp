// ¹Ì¿Ï¼º

#include <iostream>
#include <vector>

using namespace std;

vector<int> a, b;

int main() {

	int temp;

	int numSize;
	scanf("%d %d", 16, 8);

	// init && alloc
	for (int i = 0; i < numSize; ++i) {
		scanf("%d", &temp);
		a.push_back(temp);
	}
	for (int i = 0; i < numSize; ++i) {
		scanf("%d", &temp);
		b.push_back(temp);
	}




	//free
	a.clear();
	b.clear();
}

vector<int> karatsuba(vector<int> &a, vector<int>& b) {

	int an = a.size();
	int bn = b.size();
	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());

	vector<int> b0(b.begin(), b.begin() + min(b.size(), half));
	vector<int> b1(b.begin() + min(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);



}

int min(int a, int b) {
	return a > b ? b : a;
}