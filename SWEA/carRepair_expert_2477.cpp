#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct guest {
	int num;
	int t;
	int used_rec;
	int used_rep;
	guest(int _num, int _t) {
		num = _num;
		t = _t;
		used_rec = used_rep = -1;
	}
	guest() {}
};

int carRepair(int A, int B);
int find_A_B(vector<guest>& end_gst, int A, int B);
void v2q(vector<guest>& v, queue<guest>& q, int size);
bool checkUsed(vector<bool>& used, int size, int& idx);

vector<int> rec, rep;
vector<guest> gst;

int main() {
	int T;
	cin >> T;
	vector<int> result(T);

	for (int t = 0; t < T; ++t) {
		// input
		int N, M, K, A, B;
		cin >> N >> M >> K >> A >> B;

		rec = vector<int>(N, 0);
		rep = vector<int>(M, 0);
		gst = vector<guest>(K);

		for (int i = 0; i < N; ++i) {
			cin >> rec[i];
		}

		for (int i = 0; i < M; ++i) {
			cin >> rep[i];
		}

		for (int k = 1; k <= K; ++k) {
			int num = k;
			int num_t;
			cin >> num_t;
			gst[k - 1] = guest(num, num_t);
		}

		// proc
		result[t] = carRepair(A, B);

		// free
		rec.clear();
		rep.clear();
		gst.clear();
	}
	// result print
	for (int i = 0; i < result.size(); ++i) {
		cout << '#' << i + 1 << ' ' << result[i] << endl;
	}

	// result free
	result.clear();
}

int carRepair(int A, int B) {

	queue<guest> gst_q, rec_q, rep_q, rec_wait_q, rep_wait_q;
	vector<bool> rec_used(rec.size(), false), rep_used(rep.size(), false);
	vector<guest> end_g;
	int tk = 0, gCount = 0;

	// 손님 gst_q에 넣기
	v2q(gst, gst_q, gst.size());

	// 손님 다 처리 될 때 까지
	while (gCount < gst.size()) {
		// gst_q -> rec_wait_q
		vector<guest> temp;
		while (!gst_q.empty()) {
			guest g = gst_q.front();
			gst_q.pop();
			if (g.t > 0) {
				--g.t;
				temp.push_back(g);
			}
			else rec_wait_q.push(g);
		}
		v2q(temp, gst_q, temp.size());

		// rec_wait_q -> rec_q
		int idx = -1;
		while (!rec_wait_q.empty() && !checkUsed(rec_used, rec.size(), idx)) {
			guest rec_wait_g = rec_wait_q.front();
			rec_wait_q.pop();
			rec_wait_g.t = rec[idx];
			rec_wait_g.used_rec = idx;
			rec_used[idx] = true;
			rec_q.push(rec_wait_g);
		}

		// rec_q -> rep_wait_q
		vector<guest> temp1, temp_overlap;
		while (!rec_q.empty()) {
			guest rec_g = rec_q.front();
			rec_q.pop();
			if (rec_g.t > 0) {
				--rec_g.t;
				temp1.push_back(rec_g);
			}
			else {
				temp_overlap.push_back(rec_g);
				rec_used[rec_g.used_rec] = false;
			}
		}
		// 동시에 끝나는게 있는 경우
		if (temp_overlap.size() > 1) {
			sort(temp1.begin(), temp1.end(), [](guest c, guest d) -> bool {
				return c.used_rec < d.used_rec;
			});
		}
		v2q(temp1, rec_q, temp1.size());
		v2q(temp_overlap, rep_wait_q, temp_overlap.size());

		// rep_wait_q -> rep_q
		idx = -1;
		while (!rep_wait_q.empty() && !checkUsed(rep_used, rep.size(), idx)) {
			guest rep_wait_g = rep_wait_q.front();
			rep_wait_q.pop();
			rep_wait_g.t = rec[idx];
			rep_wait_g.used_rep = idx;
			rep_used[idx] = true;
			rep_q.push(rep_wait_g);
		}

		// rep_q -> gCount
		vector<guest> temp2;
		while (!rep_q.empty()) {
			guest rep_g = rep_q.front();
			rep_q.pop();
			if (rep_g.t > 0) {
				--rep_g.t;
				temp2.push_back(rep_g);
			}
			else {
				++gCount;
				end_g.push_back(rep_g);
				rep_used[rep_g.used_rep] = false;
			}
		}
		v2q(temp2, rep_q, temp2.size());
	}
	return find_A_B(end_g, A, B);
}

int find_A_B(vector<guest>& end_gst, int A, int B) {
	int ret = 0;
	for (int i = 0; i < gst.size(); ++i) {
		if (end_gst[i].used_rec == A - 1 && end_gst[i].used_rep == B - 1) ret += end_gst[i].num;
	}
	if (ret == 0) return -1;
	else return ret;
}

void v2q(vector<guest>& v, queue<guest>& q, int size) {
	for (int i = 0; i < size; ++i) {
		q.push(v[i]);
	}
}

bool checkUsed(vector<bool>& used, int size, int& idx) {
	for (int i = 0; i < size; ++i) {
		if (!used[i]) {
			idx = i;
			return false;
		}
	}
	return true;
}