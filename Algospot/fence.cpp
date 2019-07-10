#include <iostream>
#include <vector>

using namespace std;

vector<int> fence;
vector<long long> result;

long long fenceCut(int left, int right);				// ���� ū ���� �簢�� ����
long long max(long long a, long long b);
long long min(long long a, long long b);

int main() {
	// ������ �Է� ó��
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

	// ���� �Է�ó��
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

long long fenceCut(int left, int right) {				// ���� ū ���� �簢�� ����
	//base condition, ���� 1�� �϶�
	if (left == right) return fence[left];

	int mid = left + ((right - left) / 2);

	// ���� ��� ������ ���� �ִ밪 �� ū ��
	long long rst = max(fenceCut(left, mid), fenceCut(mid + 1, right));

	// ��ġ�� ���, ��ġ�� �鿡 ����ִ� ��Ÿ�� �ݵ�� ���� 
	int overlap_left = mid;
	int overlap_right = mid + 1;
	long long minHeight = min(fence[overlap_left], fence[overlap_right]);
	long long overlap_maxSquare = minHeight * (overlap_right - overlap_left + 1);

	while (overlap_left > left || overlap_right < right) {				// overlap ���� �Ѵ� left, right�� �׸�
		// overlap left, right �� fence���� ū ������, overlap_right == right�̸� left�� �����̰�
		// �� �� ��Ȳ�� �ݴ�� 
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