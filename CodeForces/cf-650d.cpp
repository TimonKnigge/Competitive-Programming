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

// Length only
template<class T>
int longest_increasing_subsequence(vector<T> &a) {
	set<T> st;
	typename set<T>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
	}
	return st.size();
}

int main() {
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<int> a(N, 0), s;
	for (int i = 0; i < N; ++i)
		scanf("%d", &a[i]);
	
	vvi Q(N, vi()), ID(N, vi());
	vvi LP(N, vi()), LS(N, vi());
	vi res(M, 0LL);
	for (int i = 0; i < M; ++i) {
		int u, b;
		scanf("%d %d", &u, &b);
		Q[u-1].push_back(b);
		LP[u-1].push_back(-1);
		LS[u-1].push_back(-1);
		ID[u-1].push_back(i);
	}
	
	int Lis = longest_increasing_subsequence<int>(a);
	
	vi lb(N, -LLINF), ub(N, LLINF);
	vector<vector<int> > lis(a.size(), vector<int>());
	vi pre(a.size(), -1);
	vii lispos(N, {-1LL, -1LL});
	int L = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		int l = 1, r = L;
		for (size_t j = 0; j < Q[i].size(); ++j) {
			l = 1; r = L;
			while (l <= r) {
				int m = (l + r + 1) / 2;
				if (a[lis[m-1].back()] < Q[i][j])
					l = m + 1;
				else	r = m - 1;
			}
			LP[i][j] = l;
		}
		l = 1;
		r = L;
		while (l <= r) {
			int m = (l + r + 1) / 2;
			if (a[lis[m - 1].back()] < a[i])
				l = m + 1;
			else
				r = m - 1;
		}
		pre[i] = (l > 1 ? lis[l - 2].back() : -1);
		lb[i] = (l > 1 ? a[lis[l-2].back()] : -LLINF);
		lis[l - 1].push_back(i); // = i;
		lispos[i] = {l-1, lis[l-1].size()-1};
		if (l > L) L = l;
		
	}
	
	vb inlis(N, false);
	vi maxsucc(N, -LLINF);
	for (int i : lis[L-1]) {
		inlis[i] = true;
	}
	vi liselem(N, 0LL);
	for (int j = L - 1; j >= 0; --j) {
		for (int i = lis[j].size() - 1; i >= 0; --i) {
			int id = lis[j][i];
			if (!inlis[id]) continue;
			liselem[j]++;
			if (pre[id] != -1) {
				maxsucc[pre[id]] = max(maxsucc[pre[id]], ll(a[id]));
				inlis[pre[id]] = true;
			}
			if (i > 0 && maxsucc[id] > a[lis[j][i-1]] && maxsucc[id] != -LLINF) {
				maxsucc[lis[j][i-1]] = max(maxsucc[lis[j][i-1]], maxsucc[id]);
				inlis[lis[j][i-1]] = true;
			}
		}
	}
	
	reverse(a.begin(), a.end());
	lis.assign(a.size(), vector<int>());
	pre.assign(a.size(), -1);
	L = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		int l = 1, r = L;
		for (size_t j = 0; j < Q[N-i-1].size(); ++j) {
			l = 1; r = L;
			while (l <= r) {
				int m = (l + r + 1) / 2;
				if (a[lis[m-1].back()] > Q[N-i-1][j])
					l = m + 1;
				else	r = m - 1;
			}
			LS[N-i-1][j] = l;
		}
		l = 1;
		r = L;
		while (l <= r) {
			int m = (l + r + 1) / 2;
			if (a[lis[m - 1].back()] > a[i])
				l = m + 1;
			else
				r = m - 1;
		}

		pre[i] = (l > 1 ? lis[l - 2].back() : -1);
		ub[N-i-1] = (l > 1 ? a[lis[l-2].back()] : LLINF);
		lis[l - 1].push_back(i); // = i;
		if (l > L) L = l;
	}
	
	reverse(a.begin(), a.end());
	
	//for (int i = 0; i < N; ++i)
	//	cerr << i << ' ' << a[i] << ' ' << inlis[i] << endl;
	
	for (int i = 0; i < N; ++i) {
		for (size_t j = 0; j < Q[i].size(); ++j) {
			int id = ID[i][j];
			res[id] = LP[i][j] + -1 + LS[i][j];
			if (res[id] < Lis) {
				// Is a the only element in its position?
				if (liselem[lispos[i].first] > 1 || !inlis[i]) {
					res[id] = Lis;
				} else { // is the new value in a small enough range?
					res[id] = Lis;
					if (Q[i][j] <= lb[i] || ub[i] <= Q[i][j]) --res[id];
				}
			}

		}

	}
	
	for (int i = 0; i < M; ++i)
		cout << res[i] << "\n";
	cout << flush;
	
	return 0;
}
