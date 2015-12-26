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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

ll gcd(ll a, ll b) {
	while (b > 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int main() {
	
	freopen("feast.in", "r", stdin);
	freopen("feast.out", "w", stdout);
	
	ll T, A, B;
	cin >> T >> A >> B;
	if (A > B) swap(A, B);
	
	vb re(T + 1, false);
	vb rr(T + 1, false);
	re[0] = true;
	ll ggd = gcd(A, B);
	for (int i = 0; i < T; i += ggd) {
		if (re[i]) {
			rr[i / 2] = true;
			if (i + A <= T) {
				re[i + A] = true;
				if (i + B <= T)
					re[i + B] = true;
			}
		}
	}
	
	for (int i = 0; i < T; ++i) {
		if (rr[i] && i + A <= T) {
			rr[i + A] = true;
			if (i + B <= T) rr[i + B] = true;
		}
	}
	
	int ans = T;
	while (!rr[ans] && !re[ans]) ans--;
	cout << ans << endl;
	
	return 0;
}
