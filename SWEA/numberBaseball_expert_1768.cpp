// user code
//
//
#define N 4



typedef struct {

	int strike;

	int ball;

} Result;



// API
void init();
Result resultCmp(int* ans, int* req);
extern Result query(int guess[]);

int valid[5040][4];
int cand[5040][4];

void doUserImplementation(int guess[]) {

	Result ret;
	ret.strike = 0;
	ret.ball = 0;

	init();

	// init guess
	guess[0] = 0;
	guess[1] = 1;
	guess[2] = 2;
	guess[3] = 3;

	ret = query(guess);
	int cand_len = 0;
	for (int i = 0; i < 5040; ++i) {
		Result bs = resultCmp(guess, valid[i]);
		if (bs.strike != ret.strike || bs.ball != ret.ball) continue;
		for (int j = 0; j < 4; ++j) {
			cand[cand_len][j] = valid[i][j];
		}
		++cand_len;
	}

	for (int i = 0; i < 4; ++i) {
		guess[i] = cand[0][i];
	}

	while (cand_len > 1) {
		ret = query(guess);
		if (ret.strike == 4) break;

		int before_len = cand_len;
		cand_len = 0;
		for (int i = 0; i < before_len; ++i) {
			Result bs = resultCmp(guess, cand[i]);
			if (bs.strike != ret.strike || bs.ball != ret.ball) continue;
			for (int j = 0; j < 4; ++j) {
				cand[cand_len][j] = cand[i][j];
			}
			++cand_len;
		}
		for (int i = 0; i < 4; ++i) {
			guess[i] = cand[0][i];
		}
	}
}

Result resultCmp(int* ans, int* req) {
	Result ret;
	ret.ball = 0;
	ret.strike = 0;

	for (int i = 0; i < 4; ++i) {
		if (ans[i] == req[i]) ret.strike++;
		for (int j = 0; j < 4; ++j) {
			if (i == j) continue;
			if (ans[i] == req[j]) ret.ball++;
		}
	}

	return ret;
}

void init() {
	int len = 0;

	for (int n1 = 0; n1 < 10; ++n1) {
		for (int n2 = 0; n2 < 10; ++n2) {
			if (n1 == n2) continue;
			for (int n3 = 0; n3 < 10; ++n3) {
				if (n1 == n3 || n2 == n3) continue;
				for (int n4 = 0; n4 < 10; ++n4) {
					if (n1 == n4 || n2 == n4 || n3 == n4) continue;
					valid[len][0] = n1;
					valid[len][1] = n2;
					valid[len][2] = n3;
					valid[len][3] = n4;
					++len;
				}
			}
		}
	}
}