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

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

ll gcd(ll a, ll b) { while (b) a %= b, swap(a, b); return a; }
ll lcm(ll n) {
	ll v = 1LL;
	while (n > 1LL) v = v / gcd(v, n) * n, --n;
	return v;
}

ll P(int s, ll N) {
	ll dv = lcm((ll)s), ret = 0LL;
	--N;

	cerr << "lcm(1.." << s << ") = " << dv << endl;

	ll cyclen = 0, cycfrac = 0;
	{
		set<ll> st;
		ll cur = 0LL;
		while (true) {
			ll mv = (cur + s + 1) % (s + 1);
			if (st.find(mv) != st.end()) break;
			cyclen++;
			if (mv != 0)
				cycfrac++;
			cur += dv;
			st.insert(mv);
		}
	}

	cerr << "cyclen = " << cyclen << ", cycfrac = " << cycfrac << endl;

	ll cur = 0LL, ans = 0LL;
	ll tms = (N - cur) / (cyclen * dv);
	cur += tms * cyclen * dv;
	ans += tms * cycfrac;

	while (cur < N) {
		if ((cur + s + 1) % (s + 1) != 0LL) ++ans;
		cur += dv;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ll ans = 0LL;
	for (int i = 1; i <= 31; ++i)
		ans += P(i, 1LL << (2 * i));
	cout << ans << endl;

	return 0;
}
