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

map<ll, ll> memo;
ll f(ll a, ll k) {
	if (a == 0) return 0;
	if (!(k&1)) {
		if (a < 3) return a;
		else return ((a + 1) % 2);
	} else {
		if (a < 4) return a % 2;
		if (a == 4) return 2;
		if (a % 2 == 1) return 0;
		auto it = memo.find(a);
		if (it != memo.end()) return it->second;
		ll v = f(a / 2, k);
		ll r = (v == 1 ? 2 : 1);
		memo.insert({a, r});
		return r;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k;
	cin >> n >> k;
	
	ll fullxor = 0LL;
	for (int i = 0; i < n; ++i) {
		ll ai;
		cin >> ai;
		fullxor = (fullxor ^ f(ai, k));
	}
	
	cout << (fullxor > 0 ? "Kevin" : "Nicky") << endl;
	
	return 0;
}
