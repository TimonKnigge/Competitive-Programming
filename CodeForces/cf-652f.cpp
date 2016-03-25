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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	ll M, T;
	cin >> N >> M >> T;
	
	vi S(N, 0LL);
	vi D(N, 0LL);
	vii Si(N, {0LL, 0LL});
	bool lf = false, rf = false;
	int dsum = 0;
	for (int i = 0; i < N; ++i) {
		char c;
		cin >> S[i] >> c;
		D[i] = (c == 'L' ? -1 : 1);
		if (D[i] == -1) lf = true; else rf = true;
		dsum += D[i];
		Si[i] = {S[i], i};
	}
	
	vi pos(N, 0LL);
	for (int i = 0; i < N; ++i) {
		pos[i] = (S[i] + D[i] * (T%M)) + M;
		pos[i] %= M;
		if (pos[i] == 0) pos[i] = M;
	}
	
	if (!lf || !rf) {
		for (int i = 0; i < N; ++i)
			cout << pos[i] << " \n"[i + 1 == N];
		return 0;
	}
	
	vii crossdir;
	for (int i = 0; i < N; ++i) {
		
		ll k = - D[i] * (D[i] == 1 ? (S[i] - 1) : S[i]);
		while (k <= 0) k += M;
		k %= M;
		if (k == 0) k += M;
		crossdir.push_back({k, D[i]});
	}
	
	sort(crossdir.begin(), crossdir.end());
	
	ll shift = -(T / M) * dsum;
	for (size_t j = 0; j < crossdir.size() && crossdir[j].first <= (T%M); ++j) {
//		cerr << crossdir[j].first << ' ' << crossdir[j].second << endl;
		shift -= crossdir[j].second;
	}
	
	shift = ((shift % N) + N) % N;
	
//	cerr << shift << endl;
	sort(pos.begin(), pos.end());
	sort(Si.begin(), Si.end());
	
	vi ans(N, 0);
	for (int i = 0; i < N; ++i) {
		ans[Si[i].second] = pos[(i + N - shift) % N];
	}
	
	for (int i = 0; i < N; ++i)
		cout << ans[i] << " \n"[i + 1 == N];
	
	return 0;
}
