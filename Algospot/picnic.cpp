#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector< vector<int> > friends;			// ģ�� ���� �׷���
vector<int> pairs;						// ¦ ���������� ����
vector<int> result;

int makePair(int frnd1);				// friend1�� ģ���ξֿ� ¦ �ΰ� ¦ �ȸ����� ã�Ƽ� �ٽ� makePair, checkPair�� true(¦ �ٸ���)�̸� ī����
int checkPair();						// ¦ �ٸ�����(pairs�� �� 0�̸�) true, ���������� false

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

int makePair(int frnd1) {				// friend1�� ģ���ξֿ� ¦ �ΰ� ¦ �ȸ����� ã�Ƽ� �ٽ� makePair, checkPair�� true(¦ �ٸ���)�̸� ī����

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

int checkPair() {						// ¦ �ٸ�����(pairs�� �� 0�̸�) -1, ���������� index return
	for (int i = 0; i < pairs.size(); i++) {
		if (pairs[i]) return i;
	}
	return -1;
}