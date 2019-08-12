#include <iostream>
#include <vector>

#define MAX_N	1000000

using namespace std;

vector<int> prime(1000000, 0);
vector<bool> check(1000002, true);

void primeCheck();
void calcPrimeSum(int num);

int main() {
	primeCheck();

	// input
	while (1) {
		int N;
		scanf("%d", &N);
		if (N == 0) break;
		calcPrimeSum(N);
	}
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

void calcPrimeSum(int num) {
	bool flag = false;
	
	int s = 0, e = 0;
	for (int i = 0; i < prime.size(); ++i) {
		if (check[num - prime[i]]) {
			s = prime[i];
			e = num - prime[i];
			flag = true;
			break;
		}
	}

	if(flag) printf("%d = %d + %d\n", num, s, e);
	else printf("Goldbach's conjecture is wrong.\n");
}

void primeCheck() {
	int prime_cnt = 0;
	for (int i = 2; i <= 1000000; ++i) {
		if (check[i]) {
			prime[prime_cnt++] = i;
			for (int j = 2; j * i <= 1000000; ++j) {
				check[j * i] = false;
			}
		}
	}
}