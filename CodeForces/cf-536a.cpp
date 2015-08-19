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

ll A, B;

bool pos(ll l, ll r, int t, int m) {
	ll tv = (r - l + 1LL) * A + (r * (r - 1) / 2 * B) - ((l - 1) * (l - 2) / 2 * B);
	ll h = A + (r - 1) * B;
	return (tv <= (ll(t) * ll(m)) && h <= t);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> A >> B >> n;
	for (int q = 1; q <= n; ++q) {
		ll l, t, m;
		cin >> l >> t >> m;
		
		if (!pos(l, l, t, m))
			cout << "-1\n";
		else {
			ll h = l, _l = l;
			while (pos(l, h, t, m)) h *= 2;
			while (l < h) {
				ll mid = (h + l) / 2;
				if (pos(_l, mid, t, m)) l = mid + 1;
				else h = mid;
			}
			cout << (l - 1) << '\n';
		}
	}
	cout << flush;
	
	return 0;
}
