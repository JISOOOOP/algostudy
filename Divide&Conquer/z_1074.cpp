#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct point {
	int r;
	int c;
};

vector<int> result;

void findNumOfZ(int size, point startPoint, point findPoint, int& findNum);			// Z순서로 몇번째인지 찾기.
int findSquareNum(int size, point startPoint, point findPoint);						// 몇사분면에 있는가

int main() {

	int N, r, c;
	scanf("%d %d %d", &N, &r, &c);

	// init && alloc
	int size = pow(2, N);
	point findPoint;
	findPoint.r = r;
	findPoint.c = c;

	int findNum = 0;
	point start;
	start.r = 0;
	start.c = 0;

	// proc
	findNumOfZ(size, start, findPoint, findNum);
	result.push_back(findNum);

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i];
	}

	// result free
	result.clear();
}

void findNumOfZ(int size, point startPoint, point findPoint, int& findNum) {
	// base condition, 찾으면 return 1, 못찾으면 카운트 업
	if (size == 1) {
		if (startPoint.r == findPoint.r && startPoint.c == findPoint.c) return ;
		else ++findNum;
	}

	// 사분면 찾고 사분면 숫자 * 1/4사각형 크기
	int squarNum = findSquareNum(size, startPoint, findPoint);
	findNum += squarNum * ((size / 2) * (size / 2));

	// 찾은 사분면의 시작점 찾고 다시 재귀
	point next;
	next.r = startPoint.r + ((size / 2) * (squarNum / 2));
	next.c = startPoint.c + ((size / 2) * (squarNum % 2));
	findNumOfZ(size / 2, next, findPoint, findNum);
}

int findSquareNum(int size, point startPoint, point findPoint){				// 몇사분면에 있는가
	if (findPoint.r < (startPoint.r + size / 2)) {							// 1 2 분면
		if (findPoint.c < (startPoint.c + size / 2)) return 0;				// 1 분면	
		else return 1;														// 2 분면
	}
	else {																	// 3 4 분면
		if (findPoint.c < (startPoint.c + size / 2)) return 2;				// 3 분면	
		else return 3;														// 4 분면
	}
}

// 처음에는 찾는 포인트까지 0,0에서 Z순서로 모두 찾아보는 방법을 선택, 입력값 N만보고 N^2이여도 (15)^2 밖에 안된다고 판단 하고 구현
// 백준 채점결과 시간초과, 다시 확인해보니 2^15^2의 어마무시한 복잡도 다른 방법을 찾아봄
// 생각해보니 각 단계에서 몇사분면에 있는지 확인해주면 단계의 시작이 사분면 숫자 - 1 * 1/4사각형 크기 임을 알게됨