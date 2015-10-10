#include <cstdio>
#include <vector>
#include <set>
using namespace std;

// Length only
template<class T>
int longest_increasing_subsequence(vector<T> &a, vector<int> &im) {
	set<T> st;
	typename set<T>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
		im[i] = st.size();
	}
	return st.size();
}

int main() {
	freopen("improvements.in", "r", stdin);
	freopen("improvements.out", "w", stdout);
	int N;
	scanf("%d", &N);
	vector<int> A(N, 0), B(N, 0), l(N, -1), r(N, -1);
	for (int i = 0; i < N; ++i) {
		int x;
		scanf("%d", &x);
		x--;
		A[x] = i;
		B[N - x - 1] = i;
	}
	
	longest_increasing_subsequence(A, l);
	longest_increasing_subsequence(B, r);
	
	int best = 0;
	for (int i = 0; i < N; ++i) {
		best = max(best, l[i] + r[N - i - 1] - 1);
	}
	printf("%d\n", best);
	
	return 0;
}
