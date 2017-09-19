#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 1000000010;
constexpr ll LLINF = 1000000000000000010LL;

struct P { bool p; int x; };

int cost(int l, int m, int r) {
	int lc = max(0, m - l), rc = max(0, r - m);
	return lc + rc + min(lc, rc);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<P> Ps;
	vector<size_t> PPs;
	{
		int N;
		string S;
		cin >> N >> S;

		for (int i = 0; i < N; ++i) {
			if (S[i] == 'P') Ps.push_back(P{ true, i});
			if (S[i] == '*') Ps.push_back(P{false, i});
		}
		sort(Ps.begin(), Ps.end(), [](const P &l, const P &r) {
			return l.x < r.x;
		});
		for (size_t i = 0; i < Ps.size(); ++i)
			if (Ps[i].p) PPs.push_back(i);
	}

	int l = 0, r = 1e7;
	while (l < r) {
		int m = (l+r) / 2;
		size_t ls = 0;
		for (size_t p : PPs) {
			if (ls >= Ps.size()) break;
			if (abs(Ps[p].x - Ps[ls].x) > m) continue;
			size_t rs = ls;
			if (rs < p) rs = p;
			while (rs + 1 < Ps.size()
					&& cost(Ps[ls].x, Ps[p].x, Ps[rs+1].x) <= m)
				++rs;
			ls = rs + 1;
		}
		if (ls >= Ps.size())
			r = m;
		else
			l = m+1;
	}

	cout << l << endl;

	return 0;
}
