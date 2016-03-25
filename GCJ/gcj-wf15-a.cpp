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
#include <unordered_map>

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

map<pair<int, int>, int> mp;
int divcon(string &S, int l, int r) {
	if (l > r) return 0;
	if (l == r) return S[l] - '0';
	else {
		auto it = mp.find({l, r});
		if (it != mp.end()) return it->second;
		int L = l, R = r + 1, ret = INF;
		while (L < R) {
			int m = (L + R) / 2;
			int lv = divcon(S, l, m - 1), rv = divcon(S, m + 1, r);
			if (lv > rv)	R = m;
			else		L = m + 1;
			ret = min(ret, (S[m] - '0') + max(lv, rv));
		}
		if (L > l) {
			--L;
			ret = min(ret, (S[L] - '0') + max(
				divcon(S, l, L - 1),
				divcon(S, L + 1, r)));
		}
		mp.insert({{l, r}, ret});
		return ret;
	}
}

int solve() {
	mp.clear();
	
	string S;
	cin >> S;
	
	return divcon(S, 0, int(S.length()) - 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t)
		cout << "Case #" << t << ": " << solve() << '\n';
	
	return 0;
}
