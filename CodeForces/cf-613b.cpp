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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll profit(vector<pair<ll, int> > &a, ll A, ll cF, ll cM, ll m, ll mn) {
	ll rem = m;
	ll ret = 0LL;
	for (int i = 0; i < int(a.size()); ++i) {
		if (a[i].first >= mn) break;
		rem -= (mn - a[i].first);
	}
	
	if (rem < 0) return -1LL;
	
	ret = mn * cM;
	int mx = 0;
	
	for (int i = int(a.size()) - 1; i >= 0; --i) {
		if (rem - (A - max(mn, a[i].first)) < 0) break;
		rem -= (A - max(mn, a[i].first));
		mx++;
	}
	ret += ll(mx) * cF;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	ll A, cF, cM, m;
	cin >> n >> A >> cF >> cM >> m;
	
	vector<pair<ll, int> > a(n, {0LL, 0});
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());
	
	ll mn = a[0].first;
	
	ll l = mn, r = A;
	while (r - l > 10) {
		ll vl = (2 * l + r) / 3, vr = (l + 2 * r) / 3;
		ll vlv = profit(a, A, cF, cM, m, vl);
		ll vrv = profit(a, A, cF, cM, m, vr);
		if (vrv == -1 || vrv < vlv)	r = vr;
		else				l = vl;
	}
	
	ll bestmn = l, bestval = profit(a, A, cF, cM, m, l);
	while (l < r) {
		++l;
		ll re = profit(a, A, cF, cM, m, l);
//		cerr << l << ' ' << re << " " << bestval << endl;
		if (re > bestval) {
			bestval = re;
			bestmn = l;
		}
	}
	
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].first >= bestmn) break;
		m -= (bestmn - a[i].first);
		a[i].first = bestmn;
	}
	for (int j = int(a.size()) - 1; j >= 0; --j) {
		if (m - (A - a[j].first) < 0) break;
		m -= A - a[j].first;
		a[j].first = A;
	}
	
	vector<ll> b(n, 0LL);
	for (int i = 0; i < n; ++i)
		b[a[i].second] = a[i].first;
	
	cout << bestval << endl;
	for (int i = 0; i < n; ++i) {
		cout << b[i];
		if (i == n-1) cout << endl;
		else cout << " ";
	}
	
	return 0;
}
