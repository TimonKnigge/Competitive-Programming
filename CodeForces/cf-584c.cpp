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

char choice(char c1, char c2) {
	if ('a' != c1 && 'a' != c2) return 'a';
	if ('b' != c1 && 'b' != c2) return 'b';
	return 'c';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, t;
	string s1, s2;
	cin >> n >> t >> s1 >> s2;
	t = n - t;
	string out = s1;
	for (int i = 0; i < n; ++i) {
		out[i] = choice(s1[i], s2[i]);
	}
//	cout << out << endl;
	vector<bool> allowed(n, true);
	for (int i = 0; t > 0 && i < n; ++i) {
		if (s1[i] != s2[i]) continue;
		out[i] = s1[i];
		allowed[i] = false;
		t--;
	}
//	cout << out << endl;
	int t1 = t, t2 = t;
	for (int i = 0; i < n && t1 > 0; ++i) {
		if (!allowed[i]) continue;
		out[i] = s1[i];
		allowed[i] = false;
		t1--;
	}
	for (int i = 0; i < n && t2 > 0; ++i) {
		if (!allowed[i]) continue;
		out[i] = s2[i];
		allowed[i] = false;
		t2--;
	}
	
	if (t1 > 0 || t2 > 0) cout << -1 << endl;
	else cout << out << endl;
	
	return 0;
}
