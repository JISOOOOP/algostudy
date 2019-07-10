#include <iostream>
#include <string>
#include <vector>

using namespace std;

string calcTime(string cur, string prom);
void conv(string s, vector<int>& t);
string calc(vector<int>& ct, vector<int>& pt);

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		string curTime, promTime;
		cin >> curTime >> promTime;

		// proc
		cout << "#" << t + 1 << " " << calcTime(curTime, promTime) << endl;

		// free
	}
}

string calcTime(string cur, string prom) {
	vector<int> ct(3, 0), pt(3, 0);
	conv(cur, ct);
	conv(prom, pt);

	return calc(ct, pt);
}

void conv(string s, vector<int>& t) {
	t[0] = ((int)s[0] - 48) * 10 + ((int)s[1] - 48);
	t[1] = ((int)s[3] - 48) * 10 + ((int)s[4] - 48);
	t[2] = ((int)s[6] - 48) * 10 + ((int)s[7] - 48);
}

string calc(vector<int>& ct, vector<int>& pt) {
	vector<int> calct(3, 0), carry(3, 0);
	string ret = "";
	calct[2] = pt[2] - ct[2];
	if (calct[2] < 0) {
		carry[1] = 1;
		calct[2] += 60;
	}

	calct[1] = pt[1] - ct[1] - carry[1];
	if (calct[1] < 0) {
		carry[0] = 1;
		calct[1] += 60;
	}

	calct[0] = pt[0] - ct[0] - carry[0];
	if (calct[0] < 0) {
		calct[0] += 24;
	}
	ret += calct[0] / 10 + 48;
	ret += calct[0] % 10 + 48;
	ret += ":";
	ret += calct[1] / 10 + 48;
	ret += calct[1] % 10 + 48;
	ret += ":";
	ret += calct[2] / 10 + 48;
	ret += calct[2] % 10 + 48;
	return ret;
}