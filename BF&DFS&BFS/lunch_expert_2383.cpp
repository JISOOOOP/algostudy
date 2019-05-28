#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct personPos {
	int num;
	int r;
	int c;
	personPos(int _num, int _r, int _c) {
		num = _num;
		r = _r;
		c = _c;
	}
};

// up right down left
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

vector< vector< vector<int> > >visited;
vector< vector<int> > room;

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input && alloc
		int N;
		cin >> N;

		room = vector< vector<int> >(N + 1, vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> room[i][j];
			}
		}

		// proc


		// free
		room.clear();

	}
}

int lunch() {
	vector<personPos> person, stair;
	findPersonStair(person, stair);

	visited = vector< vector< vector<int> > >(person.size() + 1, vector< vector<int> >(room.size(), vector<int>(room.size(), 0)));

	// bfs
	queue<personPos> step;
	for (int i = 0; i < person.size(); ++i) {
		step.push(person[i]);
		visited[person[i].num][person[i].r][person[i].c] = 1;
	}

	while (!step.empty()) {
		personPos cur = step.front();
		step.pop();

		vector<personPos> next;

		for (int i = 0; i < 4; ++i) {
			int next_r = cur.r + dr[i];
			int next_c = cur.c + dc[i];

			// outOfRange
			if (next_r < 0 || next_r >= room.size() - 1 || next_c < 0 || next_c >= room.size() - 1) continue;
			// visited
			if (visited[cur.num][next_r][next_c] == 1) continue;

			visited[cur.num][next_r][next_c] = 1;
			next.push_back(personPos(cur.num, next_r, next_c));
		}
		
		
	}
}

void findPersonStair(vector<personPos>& person, vector<personPos>& stair) {
	int count = 1;
	for (int i = 0; i < room.size() - 1; ++i) {
		for (int j = 0; j < room.size() - 1; ++j) {
			if (room[i][j] == 1) {
				person.push_back(personPos(count, i, j));
				++count;
			}
			else if (room[i][j] != 0) stair.push_back(personPos(0, i, j));
		}
	}
}