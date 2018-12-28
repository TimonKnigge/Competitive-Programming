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
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

// Need a much better hash function for gp_hash_table
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31); }
	size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM
			= chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM); } };

template<class TOut>
using table = gp_hash_table<uint64_t, TOut, custom_hash>;

ll lcm(ll a, ll b) {
	ll _a = a, _b = b;
	while (_b) _a %= _b, swap(_a, _b);
	return a / _a * b;
}
ll plcm(ll a, ll b, ll c) {
	return lcm(a, lcm(b, c) / c);
}

table<ll> cache[70][70];
ll r(int i, int n, ll m, ll v, int s) {
	if (m < v) return 0;
	if (i > n) return m / v;
	auto it = cache[i][s].find(v);
	if (it != cache[i][s].end())
		return it->second;
	ll ret = m / v;
	for (int j = i; j <= n; ++j)
		ret -= r(j+1, n, m, plcm(v, ll(j), s), s);
	cache[i][s].insert({v, ret});
	return ret;
}
ll solve(ll n, ll m) {
	for (int x = 0; x < 70; ++x)
		for (int y = 0; y < 70; ++y)
			cache[x][y].clear();
	ll ans = 0LL;
	for (int i = 1; i <= n; ++i)
		ans += r(i+1, n, m, 1LL, i);
	cout << "P(" << n << ", " << m << ") = " << ans << endl;
	return ans;
}

void solve() {
	ll p10[17];
	p10[0] = 1;
	for (int i = 1; i <= 16; ++i)
		p10[i] = 10 * p10[i-1];
		
	solve(12, 345);
	solve(32, p10[15]);
	solve(64, 64);
	for (int j = 1; j <= 16; ++j)
		solve(64, p10[j]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
