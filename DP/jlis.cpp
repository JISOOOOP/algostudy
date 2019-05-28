#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > cache;
vector<long long> seq1, seq2;
vector<int> result;

int jlis();				// seq1_start = 0~seq1.size()-1 , seq2_start = 0~seq2.size()-1 �� �غ���
int combineIs(int seq1_start, int seq2_start);

int main() {

	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; ++t) {
		int N, M;
		scanf("%d %d", &N, &M);

		// init && alloc
		for (int n = 0; n < N; ++n) {
			long long temp;
			scanf("%d", &temp);
			seq1.push_back(temp);
		}

		for (int m = 0; m < M; ++m) {
			long long temp;
			scanf("%d", &temp);
			seq2.push_back(temp);
		}

		for (int n = 0; n <= N; ++n) {
			vector<int> ele(M + 1, -1);
			cache.push_back(ele);
		}

		// proc
		result.push_back(jlis());

		// free
		seq1.clear();
		seq2.clear();
		cache.clear();
	}

	// result print
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
	}

	// result free
	result.clear();
}

int jlis() {				// seq1_start = 0~seq1.size()-1 , seq2_start = 0~seq2.size()-1 �� �غ���
	int ret = -1;

	for (int i = 0; i < seq1.size(); ++i) {
		for (int j = 0; j < seq2.size(); ++j) {
			int temp = combineIs(i, j);
			ret = (ret > temp) ? ret : temp;
		}
	}
	return ret;
}

int combineIs(int seq1_start, int seq2_start) {
	// Memoization
	int& ret = cache[seq1_start][seq2_start];
	if (ret != -1) return ret;

	ret = 1;

	// base case
	// 1. �� �� ������ Ȯ��������
	if (seq1_start == seq1.size() && seq2_start == seq2.size()) return ret = 0;

	// �� �� ���� �� ���� 
	// ���� �� ���� �� seq_start���� ū �� idx = seq_start + skip ���� ���
	int skip = 0;
	if (seq1_start != seq1.size() && (seq2_start == seq2.size() || seq1[seq1_start] < seq2[seq2_start])) {
		while (seq1_start + ++skip < seq1.size() && seq1[seq1_start] >= seq1[seq1_start + skip]);
		return ret += combineIs(seq1_start + skip, seq2_start);
	}
	// �ݴ� ����
	else if (seq2_start != seq2.size() && (seq1_start == seq1.size() || seq1[seq1_start] > seq2[seq2_start])) {
		while (seq2_start + ++skip < seq2.size() && seq2[seq2_start] >= seq2[seq2_start + skip]);
		return ret += combineIs(seq1_start, seq2_start + skip);
	}
	// ����ó��, ���� ���� ���̸� �ƹ��ų� �ϳ� ����
	else if (seq1[seq1_start] == seq2[seq2_start]) return ret = combineIs(seq1_start + 1, seq2_start);

}


// ��.. ���� �����ϱ�... �˰��� �����.. ���� ���� �� ��� ���ɴ� ���
// ���� ������ ��Ž���� ���� �� �޸������̼� �����ϴ� ������� ����
// �������� �������� ��� ������� ���ϴ� ������ ��� �������� ��쿡 �õ�
// �� �� ���� ū ���� ���
// �Է°� long long �ٲ�µ��� ����.. ����..