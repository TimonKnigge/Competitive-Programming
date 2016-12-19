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
	
	int n;
	cin >> n;
	
	int Q = 20;
	vvi ans(Q, vi(n, 0LL));	

	for (int q = 0; q < Q; ++q) {
		
		// query
		vi elems;
		int stepsize = (1 << (q/2));
		bool flag = bool(q&1);
		for (int i = 0; i < n; ++i) {
			if (((i / stepsize) % 2 == 0) ^ flag) {
				elems.push_back(i);
				ans[q][i] = -1LL;
			}
		}
		
		if (elems.size() == 0) {
			ans[q].assign(n, -1LL);
			continue;
		}
		cout << elems.size() << endl;
		for (size_t i = 0; i < elems.size(); ++i)
			cout << 1+elems[i] << " \n"[i + 1 == elems.size()];
		cout << flush;
		
		for (int i = 0; i < n; ++i) {
			ll v;
			cin >> v;
			if (ans[q][i] != -1LL) ans[q][i] = v;
		}
	}
	
	cout << -1 << endl;
	for (int i = 0; i < n; ++i) {
		ll res = -1LL;
		for (int q = 0; q < Q; ++q) {
			if (ans[q][i] != -1LL && (ans[q][i] < res
				|| res == -1LL)) {
				res = ans[q][i];
//				cerr << "Pos " << i << " query " << q << " value " << ans[q][i] << endl;
			}
		}
		cout << res;
		if (i + 1 == n) cout << endl;
		else cout << ' ';
	}
	
	return 0;
}
