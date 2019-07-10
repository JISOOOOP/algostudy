#include <iostream>
#include <vector>

using namespace std;

vector<int> arr;

void calcMaxArr();
void printArr();

int main() {
	// input
	int N;
	cin >> N;

	arr = vector<int>(N, 0);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}

	// proc
	calcMaxArr();
	printArr();

	// free
	arr.clear();
}

void calcMaxArr() {
	// pos -> nag
	int minNum = 1;
	int minIdx = -1;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] >= 0) arr[i] = -arr[i] - 1;
		if (minNum > arr[i]) {
			minNum = arr[i];
			minIdx = i;
		}
	}

	if (arr.size() % 2 == 0) return;
	else {
		arr[minIdx] = -arr[minIdx] - 1;
	}
}

void printArr() {
	for (int i = 0; i < arr.size(); ++i) {
		printf("%d ", arr[i]);
	}
}