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
	
	int t;
	cin >> t;
	
	map<string, int> cnt;
	
	while (t--) {
		char c;
		cin >> c;
		
		string s;
		cin >> s;
		while (s.length() < 20) s = "0" + s;
		
		for (size_t i = 0; i < s.length(); ++i)
			s[i] = ((s[i] - '0') % 2) + '0';
			
		if (c == '+') {
			auto it = cnt.find(s);
			if (it == cnt.end()) cnt.insert({s, 1});
			else it->second++;
		} else if (c == '-') {
			auto it = cnt.find(s);
			it->second--;
			if (it->second == 0) cnt.erase(it);
		} else {
			auto it = cnt.find(s);
			if (it != cnt.end())
				cout << it->second << endl;
			else	cout << 0 << endl;
		}
	}
	
	return 0;
}
