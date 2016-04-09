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
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		
		ll K, C, S;
		cin >> K >> C >> S;
		
		if (C * S < K)
			cout << "Case #" << t << ": IMPOSSIBLE\n";
		else {
			set<ll> ans;
			bool change = true;
			for (int p = 1; change;) {
				
				ll pre = 0LL;
				for (int j = 0; j < C; ++j) {
					pre = pre * K + (p - 1LL);
					if (p == K) change = false;
					p = p % K + 1;
				}
				ans.insert(pre + 1LL);
			}
			
//			for (ll v = 1LL; ans.size() < S; ++v)
//				if (ans.find(v) == ans.end())
//					ans.insert(v);
			
			cout << "Case #" << t << ":";
			for (ll v : ans)
				cout << ' ' << v;
			cout << '\n';
		}
	}
	
	return 0;
}
