#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct pos {
	int line;
	int idx;
	pos(int _line, int _idx) : line(_line), idx(_idx) {}
	pos() {}
};

vector<pos> numPos(10001);
vector<bool> visited;

void init(int& a, int& b);
void calcNumPos();
int proc(int start, int dst);
int max(int a, int b);
int min(int a, int b);
int _abs(int a, int b);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		int a, b;
		cin >> a >> b;

		visited = vector<bool>(10001, false);
		// proc
		init(a, b);
		cout << "#" << t + 1 << " " << proc(a, b) << endl;

		// free
		visited.clear();
	}
}

void calcNumPos() {
	int idx = 1;
	for (int i = 1; i < 10000; ++i) {
		for (int j = 1; j <= i; ++j) {
			if (idx == 10001) return;
			numPos[idx].line = i;
			numPos[idx].idx = j;
			++idx;
		}
	}
}

void init(int& a, int& b) {
	calcNumPos();
	if (a > b) {
		int temp = a;
		a = b;
		b = temp;
	}
}

int proc(int start, int dst) {
	int ret = 0;

	int lineDiff = _abs(numPos[start].line, numPos[dst].line);
	int idxDiff = _abs(numPos[start].idx, numPos[dst].idx);
	if (lineDiff < idxDiff) {
		ret = idxDiff;
		if (numPos[start].idx > numPos[dst].idx) ret += lineDiff;
	}
	else {
		ret = lineDiff;
		if (numPos[start].idx > numPos[dst].idx) ret += idxDiff;
	}
	return ret;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int _abs(int a, int b) {
	if (a < b) return b - a;
	else return a - b;
}