#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int histogram_stack(vector<int>& hist);
long long max(long long a, long long b);

int main() {

	vector<long long> result;

	while (1) {

		int N;
		cin >> N;
		if (N == 0) break;

		vector<int> hist(N + 2);

		for (int i = 1; i <= N; ++i) {
			cin >> hist[i];
		}

		result.push_back(histogram_stack(hist));

		// free
		hist.clear();
	}

	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int histogram_stack(vector<int>& hist) {

	vector<int> left(hist.size());
	vector<int> right(hist.size());
	stack<int> height;

	// init
	// 양쪽에 높이 0인 사각형 삽입
	long long maxArea = 0;
	hist[0] = 0;
	hist[hist.size() - 1] = 0;
	height.push(0);

	for (int i = 1; i < hist.size(); ++i) {
		// hist[i] > hist[i - 1]
		// i의 왼쪽 끝은 i - 1
		if (hist[i] > hist[i - 1]) {
			left[i] = i;
			height.push(i);
		}
		// hist[i] <= hist[i - 1]
		// i-1의 오른쪽 끝은 i
		else if (hist[i] <= hist[i - 1]) {
			int top = height.top();
			while (hist[i] <= hist[top]) {
				height.pop();
				if (height.empty()) break;
				right[top] = i - 1;
				left[top] = height.top() + 1;
				maxArea = max(maxArea, (long long)hist[top] * (long long)(right[top] - left[top] + 1));
				top = height.top();
			}
			height.push(i);
		}
	}

	return maxArea;
}

long long max(long long a, long long b) {
	return a > b ? a : b;
}