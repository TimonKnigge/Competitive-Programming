#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

ll gcd(ll a, ll b) {
	ll t;
	while (b != 0) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
ll lcm(ll a, ll b) { return (a / gcd(a, b) * b); }
ll lcm(vector<int> &v) {
	ll ret = -1;
	for (int i = 0; i < v.size(); ++i) {
		if (ret == -1) ret = v[i];
		else ret = lcm(ret, v[i]);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	vector<int> f(n, -1), indeg(n, 0);
	vb exist(n, true);
	for (int i = 0; i < n; ++i) {
		cin >> f[i];
		f[i]--;
		if (i != f[i])
			indeg[f[i]]++;
		else
			exist[i] = false;
	}

	ll M = 1;
	queue<int> q;
	vi len(n, 0), cyc_lens;
	for (int i = 0; i < n; ++i) if (exist[i] && indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		exist[u] = false;
		indeg[f[u]]--;
		M = max(M, ll(len[u] + 1));
		if (indeg[f[u]] == 0 && exist[f[u]]) {
			q.push(f[u]);
			len[f[u]] = max(ll(len[f[u]]), ll(len[u] + 1));
		}
	}

	// Find cycle lengths
	for (int i = 0; i < n; ++i) {
		if (!exist[i]) continue;
		int u = i, k = 0;
		while (exist[u]) {
			exist[u] = false;
			k++;
			u = f[u];
		}
		cyc_lens.push_back(k);
	}
	

	ll r = lcm(cyc_lens);
//	cerr << r << '\t' << M << endl;
	ll ans = M;
	if (r != -1) {
		ans = r * (M / r);
		while (ans < M) ans += r;
	}

	cout << ans << endl;
	
	return 0;
}
