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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	ll x1, x2;
	cin >> x1 >> x2;
	
	vector<pair<pair<ll, ll>, int> > s1, s2;
	for (int i = 0; i < n; ++i) {
		ll k, b;
		cin >> k >> b;
		ll p1 = k * x1 + b, p2 = k * x2 + b;
		s1.push_back({{p1, p2}, i});
		s2.push_back({{p2, p1}, i});
	}
	
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	
	bool imp = true;
	for (int i = 0; i < n; ++i) {
		imp = imp && s1[i].second == s2[i].second;
//		cerr << s1[i].first.first << ' ' << s1[i].first.second << endl;
	}
	
	cout << (imp ? "NO" : "YES") << endl;
	
	return 0;
}
