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

void pmap(map<int, int> &m){
	for (auto it = m.begin(); it != m.end(); ++it)
		cout << '[' << it->first << ' '  << it->second << ']' << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	
	map<int, int> mp;
	int dot = 0, start = 0, ans = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '.') dot++;
		else {
			if (dot > 0) {
				mp.insert({start, dot});
				ans += dot - 1;
			}
			dot = 0;
			start = i + 1;
		}
	}
	if (dot > 0) {
		mp.insert({start, dot});
		ans += dot - 1;
	}

	for (int q = 0; q < m; ++q) {
		int i; char c;
		cin >> i >> c;
		i--;
		if ((c == '.' && s[i] == '.')
			|| (c != '.' && s[i] != '.')) {
			cout << ans << '\n'; continue;
		}
		if (c == '.') {
			// i was a character, will be a dot
			bool ldot = (i > 0 && s[i - 1] == '.'),
				rdot = (i < n - 1 && s[i + 1] == '.');
			int st = i, c = 1;
			if (ldot) {
				auto it = mp.lower_bound(i);
				it--;
				st = it->first;
				c += it->second;
				ans -= it->second - 1;
				mp.erase(it);
			}
			if (rdot) {
				auto it = mp.find(i + 1);
				ans -= it->second - 1;
				c += it->second;
				mp.erase(it);
			}
			mp.insert({st, c});
			ans += c - 1;
		} else {
			auto it = mp.upper_bound(i);
			it--;
			int st = it->first, c = it->second;
			ans -= c - 1;
			mp.erase(it);
			if (st < i) {
				mp.insert({st, i - st});
				ans += i - st - 1;
			}
			if (st + c > i + 1) {
				mp.insert({i + 1, st + c - i - 1});
				ans += st + c - i - 2;
			}
		}
		cout << ans << '\n';
		s[i] = c;
	}
	cout << flush;
	
	return 0;
}
