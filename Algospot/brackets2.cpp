#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

vector<bool> result;

bool brackets2(string str);

int main() {

	int T;
	cin >> T;

	for (int t = 0; t < T; ++t) {
		// input
		string str;
		cin >> str;

		result.push_back(brackets2(str));
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		if (result[i]) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	// result free
	result.clear();
}

bool brackets2(string str) {

	stack<char> bracket;
	char temp;

	for (int i = 0; i < str.size(); ++i) {
		switch (str[i]) {
		case '(' :
		case '[' :
		case '{' :
			bracket.push(str[i]);
			break;
		case ')' :
			if (bracket.empty()) return false;
			temp = bracket.top();
			bracket.pop();
			if (temp != '(') return false;
			break;
		case ']' :
			if (bracket.empty()) return false;
			temp = bracket.top();
			bracket.pop();
			if (temp != '[') return false;
			break;
		case '}' :
			if (bracket.empty()) return false;
			temp = bracket.top();
			bracket.pop();
			if (temp != '{') return false;
			break;
		}
	}

	if (!bracket.empty()) return false;
	return true;
}