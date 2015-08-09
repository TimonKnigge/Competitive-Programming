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

map<int, int> has_map, need_map;
void add(int v, bool sw) {
	map<int, int> &r1 = has_map, &r2 = need_map;
	if (sw) { r1 = need_map; r2 = has_map; }
	auto it = r2.find(v);
	if (it == r2.end()) {
		it = r1.find(v);
		if (it == r1.end()) r1.insert({v, 1});
		else it->second++;
	} else {
		if (it->second == 1) r2.erase(v);
		else it->second--;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	vector<int> a(n, -1);
	for (int i = 0; i < n; ++i) cin >> a[i];
	vb pfh(n, false), pfh2(n, false);
	if (n % 2 == 1) pfh[n / 2] = true;
	else pfh[n / 2] = pfh[n / 2 + 1] = (a[n / 2] == a[n / 2 + 1]);
	for (int i = n / 2 - 1; i >= 0; --i) {
		pfh[i] = pfh[n - i - 1] = pfh[i + 1] && (a[i] == a[n - i - 1]);
	}
	pfh2[0] = pfh2[n - 1] = (a[0] == a[n - 1]);
	for (int i = 1; i < n / 2; i ++)
		pfh2[i] = pfh2[n - i - 1] = pfh2[i - 1] && (a[i] == a[n - i - 1]);

	int pb = (n % 2 == 1) ? (n / 2 - 1) : (n / 2),
	    pe = (n % 2 == 1) ? (n / 2 + 1) : (n / 2 + 1);

	ll ans = 0LL;
	int l = 0, r = -1;
	map<int, int> has_map, need_map;
	for (l = 0; l < n; ++l) {
		while (r < n && !has_map.empty() && !need_map.empty()
			&& (r > pb || pfh[r + 1])
			&& (l < pe || pfh[l - 1])) {
			r++;
			add(a[r], true);
			add(a[n - r - 1], false);
		}
		if (has_map.empty() && need_map.empty()) {
			if (
		}
		add(a[l], false);
		add(a[n - l - 1], true);
	}
	while (r < L) {
		if (a[r] != a[n - r - 1]) {
			add(a[r], false);
			add(a[n - r - 1], true);
		}
		r++;
	}

	return 0;
}
