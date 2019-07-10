#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct point {
	int r;
	int c;
};

vector<int> result;

void findNumOfZ(int size, point startPoint, point findPoint, int& findNum);			// Z������ ���°���� ã��.
int findSquareNum(int size, point startPoint, point findPoint);						// ���и鿡 �ִ°�

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
	// base condition, ã���� return 1, ��ã���� ī��Ʈ ��
	if (size == 1) {
		if (startPoint.r == findPoint.r && startPoint.c == findPoint.c) return ;
		else ++findNum;
	}

	// ��и� ã�� ��и� ���� * 1/4�簢�� ũ��
	int squarNum = findSquareNum(size, startPoint, findPoint);
	findNum += squarNum * ((size / 2) * (size / 2));

	// ã�� ��и��� ������ ã�� �ٽ� ���
	point next;
	next.r = startPoint.r + ((size / 2) * (squarNum / 2));
	next.c = startPoint.c + ((size / 2) * (squarNum % 2));
	findNumOfZ(size / 2, next, findPoint, findNum);
}

int findSquareNum(int size, point startPoint, point findPoint){				// ���и鿡 �ִ°�
	if (findPoint.r < (startPoint.r + size / 2)) {							// 1 2 �и�
		if (findPoint.c < (startPoint.c + size / 2)) return 0;				// 1 �и�	
		else return 1;														// 2 �и�
	}
	else {																	// 3 4 �и�
		if (findPoint.c < (startPoint.c + size / 2)) return 2;				// 3 �и�	
		else return 3;														// 4 �и�
	}
}

// ó������ ã�� ����Ʈ���� 0,0���� Z������ ��� ã�ƺ��� ����� ����, �Է°� N������ N^2�̿��� (15)^2 �ۿ� �ȵȴٰ� �Ǵ� �ϰ� ����
// ���� ä����� �ð��ʰ�, �ٽ� Ȯ���غ��� 2^15^2�� ������� ���⵵ �ٸ� ����� ã�ƺ�
// �����غ��� �� �ܰ迡�� ���и鿡 �ִ��� Ȯ�����ָ� �ܰ��� ������ ��и� ���� - 1 * 1/4�簢�� ũ�� ���� �˰Ե�