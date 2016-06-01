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
	
	map<int, int> mp;
	
	n--;
	int a;
	cin >> a;
	
	mp.insert({a, 0});
	
	bool f = false;
	while (n--) {
		if (f) cout << ' '; else f = true;
		
		cin >> a;
		
		auto it = mp.lower_bound(a);
		auto it2 = it;
		
		if (it2 != mp.begin()) {
			--it2;
			if (it == mp.end() || it2->second > it->second) {
				cout << it2->first;
				mp.insert({a, it2->second+1});
			} else {
				cout << it->first;
				mp.insert({a, it->second+1});
			}
		} else {
			cout << it->first;
			mp.insert({a, it->second+1});
		}
	}
	cout << endl;
	
	return 0;
}
