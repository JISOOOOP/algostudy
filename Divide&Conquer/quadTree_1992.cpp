#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector< vector<char> > matrix;
vector<string> result;

string compressQuadTree(int size, int start_r, int start_c);			// 쿼드 트리 압축
bool checkMatrix(int color, int size, int start_r, int start_c);							// 모두 color 값인지 확인, 아니면 false 맞으면 true

int main() {

	int N;
	scanf("%d", &N);

	// init && alloc
	for (int i = 0; i < N; ++i) {
		vector<char> ele;
		string str;
		cin >> str;
		for (int j = 0; j < N; j++) {
			ele.push_back(str[j]);
		}
		matrix.push_back(ele);
	}

	result.push_back(compressQuadTree(N, 0, 0));

	// free
	matrix.clear();

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();

}

string compressQuadTree(int size, int start_r, int start_c) {
	string rst = "";
	rst += matrix[start_r][start_c];
	//base condition
	if (checkMatrix(matrix[start_r][start_c], size, start_r, start_c)) return rst;
	else {
		rst = '(';
		for (int i = 0; i < 4; ++i) {
			rst += compressQuadTree(size / 2, start_r + ((i / 2) * (size / 2)), start_c + ((i % 2) * (size / 2)));
		}
		rst += ')';
	}
	return rst;
}

bool checkMatrix(int color, int size, int start_r, int start_c) {							// 모두 color 값인지 확인, 아니면 false 맞으면 true
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[start_r + i][start_c + j] != color) return false;
		}
	}
	return true;
}