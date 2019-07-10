#include <iostream>
#include <vector>

using namespace std;

vector<int> fence;
vector<long long> result;

long long fenceCut(int left, int right);				// 가장 큰 내부 사각형 컷팅
long long max(long long a, long long b);
long long min(long long a, long long b);

int main() {
	// 종만북 입력 처리
	//int T;
	//scanf("%d", &T);

	//for (int t = 0; t < T; t++) {
	//	int N;
	//	scanf("%d", &N);

	//	// init && alloc
	//	for (int i = 0; i < N; i++) {
	//		int temp;
	//		scanf("%d", &temp);
	//		fence.push_back(temp);
	//	}

	//	result.push_back(fenceCut(0, fence.size() - 1));

	//	// free
	//	fence.clear();
	//}

	// 백준 입력처리
	while (1) {
		int N;
		scanf("%d", &N);
		if (N == 0) break;

		// init && alloc
		for (int i = 0; i < N; i++) {
			int temp;
			scanf("%d", &temp);
			fence.push_back(temp);
		}

		result.push_back(fenceCut(0, fence.size() - 1));

		// free 
		fence.clear();
	}


	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

long long fenceCut(int left, int right) {				// 가장 큰 내부 사각형 컷팅
	//base condition, 판자 1개 일때
	if (left == right) return fence[left];

	int mid = left + ((right - left) / 2);

	// 왼쪽 면과 오른쪽 면의 최대값 중 큰 것
	long long rst = max(fenceCut(left, mid), fenceCut(mid + 1, right));

	// 겹치는 경우, 겹치는 면에 닿아있는 울타리 반드시 포함 
	int overlap_left = mid;
	int overlap_right = mid + 1;
	long long minHeight = min(fence[overlap_left], fence[overlap_right]);
	long long overlap_maxSquare = minHeight * (overlap_right - overlap_left + 1);

	while (overlap_left > left || overlap_right < right) {				// overlap 변수 둘다 left, right면 그만
		// overlap left, right 중 fence값이 큰 쪽으로, overlap_right == right이면 left만 움직이게
		// 그 외 상황은 반대로 
		if (overlap_left > left && ((overlap_right == right) || (fence[overlap_left - 1] >= fence[overlap_right + 1]))) {
			--overlap_left;
			minHeight = min(minHeight, fence[overlap_left]);
		}
		else {
			++overlap_right;
			minHeight = min(minHeight, fence[overlap_right]);
		}
		overlap_maxSquare = max(overlap_maxSquare, (long long)minHeight * (overlap_right - overlap_left + 1));
	}

	return rst = max(rst, overlap_maxSquare);
}

long long max(long long a, long long b) {
	return a > b ? a : b;
}

long long min(long long a, long long b) {
	return a > b ? b : a;
}