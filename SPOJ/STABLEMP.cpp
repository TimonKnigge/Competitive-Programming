#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

/*
	If m = w, the algorithm nds a complete, optimal matching. mpref[i][j] gives the id of the j'th preference of the i'th man. wpref[i][j] gives the preference the j'th woman assigns to the i'th man. Both mpref and wpref should be zero-based permutations. Complexity: O(mw)
*/

void stable_marriage(vvi &mpref, vvi &wpref, vi &mmatch) {
	size_t M = mpref.size(), W = wpref.size();
	vi wmatch(W, -1);
	mmatch.assign(M, -1);
	vector<size_t> mnext(M, 0);
	stack<size_t> st;
	for (size_t m = 0; m < M; ++m) st.push(m);

	while (!st.empty()) {
		size_t m = st.top(); st.pop();
		if (mmatch[m] != -1) continue;
		if (mnext[m] >= W) continue;

		size_t w = mpref[m][mnext[m]++];
		if (wmatch[w] == -1) {
			mmatch[m] = w;
			wmatch[w] = m;
		} else {
			size_t mp = size_t(wmatch[w]);
			if (wpref[w][m] < wpref[w][mp]) {
				mmatch[m] = w;
				wmatch[w] = m;
				mmatch[mp] = -1;
				st.push(mp);
			} else	st.push(m);
		}
	}
}

void solve() {
	int N;
	scanf("%d", &N);
	
	vvi M(N, vi(N, 0)), W(N, vi(N, 0));
	for (int i = 0; i < N; ++i) {
		scanf("%d", &i);
		--i;
		for (int j = 0; j < N; ++j) {
			int v;
			scanf("%d", &v);
			--v;
			M[i][j] = v;
		}
	}
	for (int i = 0; i < N; ++i) {
		scanf("%d", &i);
		--i;
		for (int j = 0; j < N; ++j) {
			int v;
			scanf("%d", &v);
			--v;
			W[i][v] = j;
		}
	}
	
	vi res;
	stable_marriage(M, W, res);
	for (int i = 0; i < N; ++i)
		cout << res[i]+1 << ' ' << i+1 << '\n';
}

int main() {

	int T;
	scanf("%d", &T);
	while (T--) solve();
	
	return 0;
}
