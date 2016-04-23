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
	
	string s;
	cin >> s;
	
	for (size_t i = 1; i < s.length(); ++i) {
		if (s[i] != s[i - 1])
			continue;
		s[i] = 'a';
		while (s[i] == s[i - 1] || 
			(i + 1 < s.length() && s[i] == s[i + 1]))
			++s[i];
	}
	
	cout << s << endl;
	
	return 0;
}
