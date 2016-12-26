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

template<class T>
void prtv(const vector<T> &v) {
	cerr << "{";
	for (size_t i = 0; i < v.size(); ++i) {
		cerr << v[i];
		if (i + 1 < v.size()) cerr << ",";
	}
	cerr << "}";
}

int f(vi &powers, vector<size_t> next, int lb) {
/*
	cerr << "f(";
	prtv(powers);
	cerr << ", ";
	prtv(next);
	cerr << ", ";
	cerr << lb <<")" << endl;
*/	
	// Prune.
	if (accumulate(powers.begin(), powers.end(), 0LL) / next.size() <= lb)
		return lb;

	// Try taking 'next'.
	vi npowers(powers);
	bool pos = all_of(next.begin(), next.end(), [&npowers](int i) {
		return npowers[i]-- > 0;
	});
	
	// Increase next.
	size_t nl = 0;
	while (nl < next.size() && next[nl] + 1 ==  powers.size()) ++nl;
	if (nl == next.size())
		next.assign(next.size() + 1, 0LL);
	else for (size_t i = 0; i <= nl; ++i)
		next[i] = next[nl] + 1;
	
	// Pick best.
	if (pos) lb = max(lb, 1 + f(npowers, next, max(lb - 1, 0)));
	return max(lb, f(powers, next, lb));
}

int main() {
	ll X;
	cin >> X;
	
	int singles = 0;
	vi powers;
	
	int d = 0;
	while (1&~X) ++d, X >>= 1;
	if (d > 0) {
		++singles;
		if (d > 1) powers.push_back(d - 1);
	}
	d = 0;
	while (X % 3 == 0LL) ++d, X /= 3LL;
	if (d > 0) {
		++singles;
		if (d > 1) powers.push_back(d - 1);
	}
	
	for (ll p = 5LL; p * p <= X; p += 6LL) {
		d = 0;
		while (X % p == 0LL) ++d, X /= p;
		if (d > 0) {
			++singles;
			if (d > 1) powers.push_back(d - 1);
		}
		d = 0;
		while (X % (p + 2LL) == 0LL) ++d, X /= p + 2LL;
		if (d > 0) {
			++singles;
			if (d > 1) powers.push_back(d - 1);
		}
	}
	if (X > 1LL) ++singles;

	sort(powers.rbegin(), powers.rend());
	
	cout << singles + f(powers, vector<size_t>{0, 0}, 0) << endl;
	
	return 0;
}
