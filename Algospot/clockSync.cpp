#include <iostream>
#include <vector>

#define MAX_CLOCK	16
#define MAX_SWT		10
#define UNIT_TIME	3
#define MATCH_TIME	12
#define MAX_COUNT	99999
#define UNIT_CYCLE	4

using namespace std;

bool clockSwitch[10][16] = {
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},			// #0 0 1 2
	{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},			// #1 3 7 9 11
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},			// #2 4 10 14 15
	{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},			// #3 0 4 5 6 7
	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},			// #4 6 7 8 10 12
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},			// #5 0 2 14 15
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},			// #6 3 14 15
	{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},			// #7 4 5 7 14 15
	{0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},			// #8 1 2 3 4 5
	{0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}			// #9 3 4 5 9 13
};

vector<int> clockArr;
vector<int> result;

bool findNotTwelve();											// 12시 안가리키는 시계 찾기, 있으면 false 없으면 true
int makeTwelveClock(int swtchNum);								// 0 - 15번 스위치 0 - 3번씩 모두 눌러보기
void pushSwitch(int num);										// 스위치 누르면 연결된 시계 + 3시간
int min(int a, int b);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {

		//init && alloc && input
		for (int i = 0; i < MAX_CLOCK; i++) {
			int time;
			scanf("%d", &time);
			clockArr.push_back(time);
		}

		int temp = makeTwelveClock(0);
		if (temp == MAX_COUNT) result.push_back(-1);
		else result.push_back(temp);

		//free
		clockArr.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		printf("%d\n", result[i]);
	}

}

int makeTwelveClock(int swtchNum) {							// 0 - 15번 스위치 0 - 3번씩 모두 눌러보기
	if (swtchNum == MAX_SWT) return findNotTwelve() ? 0 : MAX_COUNT;

	int rst = MAX_COUNT;

	for (int i = 0; i < UNIT_CYCLE; ++i) {
		rst = min(rst, i + makeTwelveClock(swtchNum + 1));
		pushSwitch(swtchNum);
	}

	return rst;
}

bool findNotTwelve() {							// 12시 안가리키는 시계 찾기, 있으면 false 없으면 true
	for (int i = 0; i < MAX_CLOCK; i++) {
		if (clockArr[i] != 12) return false;
	}
	return true;
}

void pushSwitch(int num) {						// 스위치 누르면 연결된 시계 + 3시간
	for (int i = 0; i < MAX_CLOCK; i++) {
		if (clockSwitch[num][i]) {
			clockArr[i] += UNIT_TIME;
			if(clockArr[i] > MATCH_TIME) clockArr[i] -= MATCH_TIME;
		}
	}
}

int min(int a, int b) {
	return (a > b) ? b : a;
}

