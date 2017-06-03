#include <bits/stdc++.h>

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

template <class T>
int getid(unordered_map<T, int> &mp, T &s) {
	auto it = mp.find(s);
	if (it == mp.end()) {
		int id = (int)mp.size();
		mp.insert({s, id});
		return id;
	} else	return it->second;
}

vi get_independent_sets(vi &nb) {
	int n = (int)nb.size();
	vi s(1<<n, 0LL);
	s[0] = 1LL;
	for (int i = 1; i < (1<<n); ++i) {
		int v = 0;
		while (((i>>v)&1) == 0) ++v;
		s[i] = s[i&~(1<<v)] + s[i&~(nb[v]|(1<<v))];
	}
	return s;
}

ll pw(ll v, int k) {
	if (k == 0) return 1LL;
	if (k == 1) return v;
	ll r = pw(v*v, k/2);
	if (k&1) r *= v;
	return r;
}

int solve(vi &nb) {
	int n = (int)nb.size(), a = (1<<n)-1;
	vi s = get_independent_sets(nb);
	for (int k = 1; k < n; ++k) {
		ll ck = 0LL;
		for (int i = 0; i < (1<<n); ++i) {
			ck += ((__builtin_popcount(i)&1) ? -1 : 1)
				* pw(s[a&~i], k);
		}
		if (ck > 0) return k;
	}
	return n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		
		unordered_map<string, int> mp;
		vvi E(n, vi());
		while (m--) {
			string l, r;
			cin >> l >> r;
			int u = getid<string>(mp, l), v = getid<string>(mp, r);
			E[u].push_back(v);
			E[v].push_back(u);
		}
		
		int ans = 1;
		vb vis(n, false);
		for (int i = 0; i < n; ++i) {
			if (vis[i]) continue;
			unordered_map<int, int> mp2;
			queue<int> q; q.push(i);
			while (!q.empty()) {
				int u = q.front(); q.pop();
				mp2.insert({u, (int)mp2.size()});
				vis[u] = true;
				for (int v : E[u]) if (!vis[v]) q.push(v);
			}
			
			vi nb(mp2.size(), 0LL);
			for (ii pr : mp2) {
				int u = pr.first, id = pr.second;
				for (int v : E[u])
					nb[id] |= (1LL << getid<int>(mp2, v));
			}
			ans = max(ans, solve(nb));
		}
		cout << ans << endl;
	}
	
	return 0;
}
