#include <cstdio>
#include <set>
#include <vector>

using namespace std;

// Entire sequence (indices)
template<class T>
int longest_increasing_subsequence(vector<T> &a, vector<int> &seq) {
	vector<int> lis(a.size(), 0), pre(a.size(), -1);
	int L = 0;
	for (int i = 0; i < a.size(); ++i) {
		int l = 1, r = L;
		while (l <= r) {
			int m = (l + r + 1) / 2;
			if (a[lis[m - 1]] < a[i])
				l = m + 1;
			else
				r = m - 1;
		}

		pre[i] = (l > 1 ? lis[l - 2] : -1);
		lis[l - 1] = i;
		if (l > L) L = l;
	}

	seq.assign(L, -1);
	int j = lis[L - 1];
	for (int i = L - 1; i >= 0; --i) {
		seq[i] = j;
		j = pre[j];
	}
	return L;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);
		vector<int> p(N, -1);
		for (int i = 0; i < N; ++i) {
			int x;
			scanf("%d", &x);
			p[x] = i;
		}
		
		vector<int> p2(N, -1), seq;
		for (int i = 0; i < N; ++i) {
			int x;
			scanf("%d", &x);
			p2[i] = p[x];
		}
		
		printf("%d\n", longest_increasing_subsequence(p2, seq));
	}
}
