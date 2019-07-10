#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ITEM {
	string itemName;
	int vol;
	int wnt;
};

vector< vector<int> > cache;
vector<ITEM> item;
vector<int> packingItem;

int calcMaxWnt(int start, int vol);
int packing(int W, vector<int>& packingItem);

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input && init && alloc
		int N, W;
		cin >> N >> W;

		for (int n = 0; n < N; ++n) {
			ITEM temp;
			cin >> temp.itemName >> temp.vol >> temp.wnt;
			item.push_back(temp);
		}

		for (int n = 0; n < N; ++n) {
			vector<int> ele(W + 1, -1);
			cache.push_back(ele);
		}

		// proc
		cout << packing(W, packingItem) << ' ';
		cout << packingItem.size() << endl;
		for (int i = 0; i < packingItem.size(); ++i) {
			cout << item[packingItem[i]].itemName << endl;
		}

		// free
		cache.clear();
		packingItem.clear();
		item.clear();
	}
}

int packing(int W, vector<int>& packingItem) {
	// calculation Max Want
	int max = calcMaxWnt(0, W);

	int vol = W;

	// 가져갈 품목 무엇인지 계산
	// cache[i][vol]과 cache[i+1][vol]이 같으면 item[i] 사용x
	for (int i = 0; i < item.size(); ++i) {
		if (calcMaxWnt(i, vol) != calcMaxWnt(i + 1, vol)) {
			packingItem.push_back(i);
			vol -= item[i].vol;
		}
	}

	return max;
}

int calcMaxWnt(int start, int vol) {
	// base case
	if (vol <= 0) return 0;
	if (start >= item.size()) return 0;

	// memoization
	int& ret = cache[start][vol];
	if (ret != -1) return ret;

	int temp = 0;

	// item[start] 가져감
	if (vol - item[start].vol >= 0) temp = item[start].wnt + calcMaxWnt(start + 1, vol - item[start].vol);
	if (temp > ret) ret = temp;

	// item[start] 안가져감
	temp = calcMaxWnt(start + 1, vol);
	if (temp > ret) ret = temp;

	return ret;
}