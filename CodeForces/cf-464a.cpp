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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

bool lowest(string &s, int pos, int p, char &val) {
	char v = s[pos];
	if (v - 'a' >= p) return false;
	while (v - 'a' < p) {
		if (pos > 0 && s[pos-1] == v) ++v;
		else if (pos > 1 && s[pos-2] == v) ++v;
		else break;
	}
	if (v - 'a' >= p) return false;
	val = v;
	return true; 
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, p;
	cin >> n >> p;
	
	string s;
	cin >> s;
	
	int i = n - 1;
	while (i >= 0) {
		char c;
		++s[i];
		if (lowest(s, i, p, c)) {
			s[i] = c;
			break;
		} else {
			s[i] = 'a';
			--i;
		}
	}
	
	if (i < 0) cout << "NO" << endl;
	else {
		bool y = true;
		char c;
		for (i = i + 1; i < n; ++i) {
			y = y && lowest(s, i, p, c);
			s[i] = c;
		}
		if (!y) cout << "NO" << endl;
		else cout << s << endl;
	}
	
	return 0;
}
