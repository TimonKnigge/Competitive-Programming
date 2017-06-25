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

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

struct abc {
	ll a, b, c;
};

ll remove_from_front(map<ll, ll> &pareto, ll a, ll b, ll ma, ll mb) {
	auto ait = pareto.find(a);
	pareto.erase(ait);
	auto it = pareto.lower_bound(a);
	mb = max(mb, it->second);
	--it;
	ma = max(ma, it->first);
	return max(0LL, a - ma) * max(0LL, b - mb);
}

ll insert_in_front(map<ll, ll> &pareto, ll a, ll b, ll ma, ll mb) {
	ll ret = 0LL;
	// Remove covers
	while (true) {
		auto it = pareto.lower_bound(a);
		if (it->second >= b) return 0LL;
		while (it->first > a) --it;
		if (it->second > b) break;
		ll ra = it->first, rb = it->second;
		ret += remove_from_front(pareto, ra, rb, ma, mb);
	}
	
	auto it = pareto.lower_bound(a);
	mb = max(mb, it->second);
	--it;
	ma = max(ma, it->first);
	ret -= max(0LL, a - ma) * max(0LL, b - mb);
	pareto.insert({a, b});
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	ll p, q, r;
	cin >> n >> p >> q >> r;
	vector<abc> vs(n, {0, 0, 0});
	for (abc &v : vs) cin >> v.a >> v.b >> v.c;
	
	sort(vs.begin(), vs.end(), [](const abc &l, const abc &r) {
		return l.c < r.c; });
	vi amax(n, 0LL), bmax(n, 0LL);
	amax.back() = vs.back().a;
	bmax.back() = vs.back().b;
	for (int i = n - 2; i >= 0; --i)
		amax[i] = max(amax[i + 1], vs[i].a),
		bmax[i] = max(bmax[i + 1], vs[i].b);
	
	ll cur = (p - amax[0]) * (q - bmax[0]), ans = 0LL;
	map<ll, ll> pareto;
	pareto.insert({0LL, q+1LL});
	pareto.insert({p+1LL, 0LL});
	int i = 0;
	for (ll c = 1LL; c <= r; ++c) {
		ans += cur;
		
//		cerr << "Pareto front" << endl;
//		for (auto it : pareto)
//			cerr << ' ' << it.first << ' ' << it.second  << endl;
		
		// changes?
		for (; i < n && vs[i].c == c; ++i) {
			// add (ai, bi) to the pareto front
			ll ai = vs[i].a, bi = vs[i].b;
			cur += insert_in_front(
				pareto, ai, bi, amax[i], bmax[i]);
//			cerr << "Inserted " << i << endl;
			
			ll af = amax[i], bf = bmax[i];
			ll at = (i + 1 < n ? amax[i + 1] : 0LL),
				bt = (i + 1 < n ? bmax[i + 1] : 0LL);
			if (af == at && bf == bt) continue;
			
			auto it = pareto.lower_bound(af);
			while (it->first > at) {
				auto it2 = it; --it2;
				ll h = it->second;
				cur += (min(af, it->first)
					- max(at, it2->first))
					* (q - max(h, bf));
				it = it2;
			}
			
			ll l = 0LL, r = p;
			while (l < r) {
				ll m = (l+r+1)/2LL;
				auto it = pareto.lower_bound(m);
				if (it->second > bf)
					l = m;
				else	r = m - 1;
			}
			it = pareto.lower_bound(l);
			while (it->second > bt) {
				auto it2 = it; ++it2;
				ll h = it->first;
				cur += (min(bf, it->second)
					- max(bt, it2->second))
					* (p - max(h, at));
				it = it2;
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
