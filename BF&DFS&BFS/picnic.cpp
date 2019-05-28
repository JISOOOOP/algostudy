#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector< vector<int> > friends;			// 친구 관계 그래프
vector<int> pairs;						// 짝 지어졌는지 여부
vector<int> result;

int makePair(int frnd1);				// friend1과 친구인애와 짝 맺고 짝 안맺은애 찾아서 다시 makePair, checkPair가 true(짝 다맺음)이면 카운팅
int checkPair();						// 짝 다맺으면(pairs가 다 0이면) true, 남아있으면 false

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {

		int N, M;
		scanf("%d %d", &N, &M);

		
		// init & alloc
		for (int n = 0; n < N; n++) {
			pairs.push_back(1);
			vector<int> ele(N, 0);
			friends.push_back(ele);
		}

		for (int m = 0; m < M; m++) {
			int frnd1, frnd2;
			scanf("%d %d", &frnd1, &frnd2);
			friends[frnd1][frnd2] = 1;
			friends[frnd2][frnd1] = 1;
		}

		result.push_back(makePair(0));

		// free
		pairs.clear();
		friends.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		printf("%d\n", result[i]);
	}
}

int makePair(int frnd1) {				// friend1과 친구인애와 짝 맺고 짝 안맺은애 찾아서 다시 makePair, checkPair가 true(짝 다맺음)이면 카운팅

	int rst = 0, next = 0;

	for (int i = frnd1; i < pairs.size(); i++) {
		if (friends[frnd1][i] && pairs[i]) {
			pairs[frnd1] = 0;
			pairs[i] = 0;
			next = checkPair();
			if (next == -1) rst = 1;
			else rst += makePair(next);
			pairs[frnd1] = 1;
			pairs[i] = 1;
		}
	}

	return rst;
}

int checkPair() {						// 짝 다맺으면(pairs가 다 0이면) -1, 남아있으면 index return
	for (int i = 0; i < pairs.size(); i++) {
		if (pairs[i]) return i;
	}
	return -1;
}