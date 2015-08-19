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

void zalgo(string &s, vi &Z) {
	Z.assign(s.length(), -1);
	int L = 0, R = 0, n = s.length();
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else if (Z[i - L] >= R - i + 1) {
			L = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else Z[i] = Z[i - L];
	}
	Z[0] = n;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	string p;
	cin >> p;
	
	vb cov(n, false);
	for (int i = 0; i < m; ++i) {
		int x;
		cin >> x;
		x--;
		cov[x] = true;
	}

	vi zf;
	zalgo(p, zf);

	int l = 0;
	ll ans = 1;
	for (int i = 0; i < n; ++i) {
		if (cov[i]) {
			if (l > 0) {
				if (zf[p.length() - l] + p.length() - l < p.length()) {
					ans = 0;
//	cerr << i << ' ' << zf[p.length() - l] << ' ' << l << endl;
				}
			}
			l = p.length();
		}
		if (l > 0) cov[i] = true;
		else ans = (ans * 26) % 1000000007;
		l--;
	}

	cout << ans << endl;
	
	return 0;
}
