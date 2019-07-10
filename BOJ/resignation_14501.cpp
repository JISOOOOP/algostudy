#include <iostream>
#include <vector>

#define MIN_VALUE	-9999

using namespace std;

vector<int> costDay;
vector<int> benefit;
vector<int> dp;
vector<int> result;

int maxBenefit(int day);		// �ִ� ���� ã��
int max(int a, int b);

int main() {

	int N;
	scanf("%d", &N);

	// init && alloc
	for (int i = 0; i < N; i++) {
		int ti, pi;
		scanf("%d %d", &ti, &pi);
		costDay.push_back(ti);
		benefit.push_back(pi);
		dp.push_back(-1);
	}

	result.push_back(maxBenefit(0));

	// free
	costDay.clear();
	benefit.clear();
	dp.clear();

	// result print
	for (int i = 0; i < result.size(); i++) {
		printf("%d", result[i]);
	}

	// result free
	result.clear();
}

int maxBenefit(int day) {		// �ִ� ���� ã��
	// base case, 
	if (day == costDay.size()) return 0;
	if (day > costDay.size()) return MIN_VALUE;

	if (dp[day] > 0) return dp[day];

	// max(i�� ��o ���, i�� ��x ���)
	return dp[day] = max(benefit[day] + maxBenefit(day + costDay[day]), maxBenefit(day + 1));	
	
}

int max(int a, int b) {
	return a > b ? a : b;
}