#include <iostream>
#include <vector>
#include <algorithm>

#define DWARF_NUM		9

using namespace std;

vector<int> dwarf;
vector<int> selected;
vector<int> result;

int findDwarf(int findSum, int curSum, int num, int dwarfNum);	// findSum이 되는 num명의 난쟁이 찾기
int findselectedDwarf(int start);									// 선택안된 난쟁이 찾기

int main() {

	// init & alloc
	for (int i = 0; i < DWARF_NUM; ++i) {
		int height;
		scanf("%d", &height);
		dwarf.push_back(height);
		selected.push_back(1);
	}

	// 2명의 키 = 난쟁이 키의 합 - 100 
	int heightSum = 0, twoSum = 0;
	for (int i = 0; i < DWARF_NUM; ++i) {
		heightSum += dwarf[i];
	}
	twoSum = heightSum - 100;

	if (findDwarf(twoSum, 0, 2, 0)) {
		for (int i = 0; i < DWARF_NUM; ++i) {
			if (selected[i]) result.push_back(dwarf[i]);
		}
	}
	sort(result.begin(), result.end());

	// free
	dwarf.clear();

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int findDwarf(int findSum, int curSum, int num, int dwarfNum) {				// findSum이 되는 num명의 난쟁이 찾기
	// base condition, num명 다뽑았으면 합이 맞는지 확인
	if (num == 0) {
		if (findSum == curSum) return 1;
		else return 0;
	}

	while (dwarfNum != -1) {
		dwarfNum = findselectedDwarf(dwarfNum);
		if (dwarfNum == -1) return 0;
		selected[dwarfNum] = 0;
		if (findDwarf(findSum, curSum + dwarf[dwarfNum], num - 1, dwarfNum)) return 1;
		selected[dwarfNum] = 1;
		++dwarfNum;
	}
}

int findselectedDwarf(int start) {					// 선택안된 난쟁이 찾기
	for (int i = start; i < DWARF_NUM; ++i) {
		if (selected[i]) return i;
	}
	return -1;
}