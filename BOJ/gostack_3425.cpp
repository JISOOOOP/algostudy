#include <iostream>

#define MAX_NUM 1000000000

using namespace std;

template <class T>

class _stack {
public:
	struct Node {
		T val;
		Node *next;
		Node() {}
		Node(T val) : val(val), next(0) {}
	};

	Node *head;
	int _size;

	_stack() {
		head = 0;
		_size = 0;
	}
	
	void push(T val) {
		Node *temp = new Node(val);
		if (head == 0) {
			head = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
	}

	void pop() {
		Node *temp = head;
		head = head->next;
		delete temp;
		_size--;
	}

	bool empty() {
		return _size == 0;
	}

	T top() {
		return head->val;
	}

	int size() {
		return head->size;
	}
};

template <class T>

class _gostack {
public:
	_stack<T> stack;

	gostack() {
		stack = new _stack<T>;
	}

	void NUM(T X) {
		stack.push(X);
	}

	bool POP() {
		if (stack.empty()) return false;
		stack.pop();
	}

	bool INV() {
		if (stack.empty()) return false;
		T temp = stack.top();
		temp = -temp;
		stack.pop();
		stack.push(temp);
	}

	bool DUP() {
		if (stack.empty()) return false;
		stack.push(stack.top());
	}

	bool _pop_pop(T& frst, T& scnd) {
		if (stack.size() < 2) return false;
		first = stack.top();
		stack.pop();
		second = stack.top();
		stack.pop();
	}

	bool SWP() {
		if (stack.size() < 2) return false;
		T frst, scnd;
		_pop_pop(frst, scnd);

		stack.push(frst);
		stack.push(scnd);
	}

	bool ADD() {
		if (stack.size() < 2) return false;
		T frst, scnd;
		_pop_pop(frst, scnd);
		if (frst + scnd > MAX_NUM) return false;
		stack.push(frst + scnd);
	}

	bool SUB() {
		if (stack.size() < 2) return false;
		T frst, scnd;
		_pop_pop(frst, scnd);
		if (frst - scnd > MAX_NUM) return false;
		stack.push(scnd - frst);
	}

	bool MUL() {
		if (stack.size() < 2) return false;
		T frst, scnd;
		_pop_pop(frst, scnd);
		if (frst * scnd > MAX_NUM) return false;
		stack.push(frst * scnd);
	}

	bool DIV() {
		if (stack.size() < 2) return false;
		int sign = 1;
		if (frst < 0) {
			frst = -frst;
			sign *= -1;
		}
		if (scnd < 0) {
			scnd = -scnd;
			sign *= -1;
		}
		T frst, scnd;
		_pop_pop(frst, scnd);
		if (frst == 0) return false;
		if ((scnd / frst) * sign > MAX_NUM) return false;
		stack.push((scnd / frst) * sign);
	}

	bool MOD() {
		if (stack.size() < 2) return false;
		int sign = 1;
		if (frst < 0) {
			frst = -frst;
			sign *= -1;
		}
		if (scnd < 0) {
			scnd = -scnd;
			sign *= -1;
		}
		T frst, scnd;
		_pop_pop(frst, scnd);
		if (frst == 0) return false;
		if ((scnd % frst) * sign > MAX_NUM) return false;
		stack.push((scnd % frst) * sign);
	}

	bool END() {
		if (stack.size() != 1) return false;
		printf("%d\n", stack.top());
	}
};

int op[100000];
int num[100000];

int main() {

	int opCnt = 0;
	int numCnt = 0;
	// op input
	while (1) {
		char temp[4];
		scanf_s("%s", temp, 4);
		int opNum = opCmp(temp);
		if (opNum == 0) scanf_s("%d", &num[numCnt++], 4);
		if (opNum == 10) break;
		if (opNum == 11) break;
		opCnt++;
	}

	// proc


}

int opCmp(char *str) {
	if (str[0] == 'N') {
		if (str[1] == 'U') {
			if (str[2] == 'M') return 0;
		}
	}

	if (str[0] == 'P') {
		if (str[1] == 'O') {
			if (str[2] == 'P') return 1;
		}
	}

	if (str[0] == 'I') {
		if (str[1] == 'N') {
			if (str[2] == 'V') return 2;
		}
	}

	if (str[0] == 'D') {
		if (str[1] == 'U') {
			if (str[2] == 'P') return 3;
		}
	}

	if (str[0] == 'S') {
		if (str[1] == 'W') {
			if (str[2] == 'P') return 4;
		}
	}

	if (str[0] == 'A') {
		if (str[1] == 'D') {
			if (str[2] == 'D') return 5;
		}
	}

	if (str[0] == 'S') {
		if (str[1] == 'U') {
			if (str[2] == 'B') return 6;
		}
	}

	if (str[0] == 'M') {
		if (str[1] == 'U') {
			if (str[2] == 'L') return 7;
		}
	}

	if (str[0] == 'D') {
		if (str[1] == 'I') {
			if (str[2] == 'V') return 8;
		}
	}

	if (str[0] == 'M') {
		if (str[1] == 'O') {
			if (str[2] == 'D') return 9;
		}
	}

	if (str[0] == 'E') {
		if (str[1] == 'N') {
			if (str[2] == 'D') return 10;
		}
	}

	if (str[0] == 'Q') {
		if (str[1] == 'U') {
			if (str[2] == 'I') return 11;
		}
	}
}