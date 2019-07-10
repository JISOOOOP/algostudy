#include <iostream>
#include <vector>
#include <algorithm>

#define DWARF_NUM		9

using namespace std;

vector<int> dwarf;
vector<int> selected;
vector<int> result;

int findDwarf(int findSum, int curSum, int num, int dwarfNum);	// findSum�� �Ǵ� num���� ������ ã��
int findselectedDwarf(int start);									// ���þȵ� ������ ã��

int main() {

	// init & alloc
	for (int i = 0; i < DWARF_NUM; ++i) {
		int height;
		scanf("%d", &height);
		dwarf.push_back(height);
		selected.push_back(1);
	}

	// 2���� Ű = ������ Ű�� �� - 100 
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

int findDwarf(int findSum, int curSum, int num, int dwarfNum) {				// findSum�� �Ǵ� num���� ������ ã��
	// base condition, num�� �ٻ̾����� ���� �´��� Ȯ��
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

int findselectedDwarf(int start) {					// ���þȵ� ������ ã��
	for (int i = start; i < DWARF_NUM; ++i) {
		if (selected[i]) return i;
	}
	return -1;
}