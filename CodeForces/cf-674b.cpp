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
	
	int n, k, a, b, c, d;
	cin >> n >> k >> a >> b >> c >> d;
	
	if (n < 5 || k < n + 1) {
		cout << -1 << endl;
		return 0;
	}
	
	set<int> abcd;
	abcd.insert(a);
	abcd.insert(b);
	abcd.insert(c);
	abcd.insert(d);
	
	vi seq;
	for (int i = 1; i <= n; ++i)
		if (abcd.find(i) == abcd.end())
			seq.push_back(i);
	
	cout << a << ' ' << c;
	for (size_t j = 0; j < seq.size(); ++j)
		cout << ' ' << seq[j];
	cout << ' ' << d << ' ' << b << endl;
	cout << c << ' ' << a;
	for (size_t j = 0; j < seq.size(); ++j)
		cout << ' ' << seq[j];
	cout << ' ' << b << ' ' << d << endl;
	
	return 0;
}
