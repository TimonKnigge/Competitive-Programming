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

ll mfind(map<char, ll> &id, char c) {
	auto it = id.find(c);
	if (it == id.end()) {
		id.insert({c, id.size()});
		return id.size() - 1;
	} else return it->second;
}

void ss(ll &v, ll l, ll r) {
	if (l == LLINF || r == LLINF) return;
	v = min(v, l+r);
}

void f() {
	string S;
	getline(cin, S);
	
	map<char, ll> id;
	vvi pos(256, vi());
	vector<ll> mpos(S.length(), 0);
	for (ll i = 0; i < (ll)S.length(); ++i) {
		ll mid = mfind(id, S[i]);
		mpos[i] = pos[mid].size();
		pos[mid].push_back(i);
	}
	
	vvi dp(S.length(), vi(S.length(), LLINF));
	for (ll r = 0; r < (ll)S.length(); ++r) {
		for (ll l = r; l >= 0; --l) {
			dp[l][r] = 3LL * (r - l + 1LL);
			// Solve [l, r]
			for (ll m = l; m < r; ++m)
				ss(dp[l][r], dp[l][m], dp[m+1][r]);
			if (S[l] == S[r]) { // Consider storing S[l]
				vi &p = pos[mfind(id, S[l])];
				ll li = mpos[l], ri = mpos[r];
				vi tdp(ri - li + 1, LLINF);
				tdp[0] = 3LL;
				for (ll i = li + 1; i <= ri; ++i) {
					tdp[i - li] = tdp[0] + 1LL;
					if (p[li] + 1 < p[i])
						tdp[i - li] += dp[p[li]+1][p[i]-1];
					for (ll j = li + 1; j < i; ++j) {
						ll tv = tdp[j - li] + 1LL;
						if (p[j] + 1 < p[i])
							tv += dp[p[j]+1][p[i]-1];
						if (tv < tdp[i - li]) tdp[i - li] = tv;
					}
				}
				if (tdp.back() < dp[l][r]) dp[l][r] = tdp.back();
			}
		}
	}
	cout << dp[0].back() << endl;
}

int main() {
	
	int N;
	cin >> N >> ws;
	while (N--) f();
	
	return 0;
}
