#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

bool cardVisited[11];
bool visited[100000000];

vector<int> card;

void proc(int taken, int takenNum, int k, int& ret);

int main() {
	int N, K;
	cin >> N >> K;

	card = vector<int>(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> card[i];
	}

	memset(visited, false, sizeof(visited));
	memset(cardVisited, false, sizeof(cardVisited));

	int ret = 0;
	proc(0, 0, K, ret);
	cout << ret << endl;
}

void proc(int taken, int takenNum, int k, int& ret) {
	// base case
	if (taken == k) {
		if (!visited[takenNum]) {
			++ret;
			visited[takenNum] = true;
		}
		return;
	}

	for (int i = 0; i < card.size(); ++i) {
		if (!cardVisited[i]) {
			cardVisited[i] = true;
			if(card[i] < 10) proc(taken + 1, takenNum * 10 + card[i], k, ret);
			else proc(taken + 1, takenNum * 100 + card[i], k, ret);
			cardVisited[i] = false;
		}
	}
}