#include <iostream> 
#include <fstream>
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

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

ll calc(vi &l, vi &r) {
	vi posof(l.size(), 0);
	FenwickTree<ll> ft(l.size());
	for (size_t i = 0; i < l.size(); ++i) posof[l[i]] = i+1;
	ll ret = 0LL;
	for (ll v : r)
		ret += ft.query(posof[v], r.size()), ft.update(posof[v], 1);
	ll cur = ret;
	for (ll v : r)
		cur += ll(r.size()) - 2 * posof[v] + 1LL,
		ret = min(ret, cur);
	return ret;
}

int main() {
	ifstream fin("mincross.in");
	ofstream fout("mincross.out");

	int N;
	fin >> N;
	vi q(N, 0LL), p(N, 0LL);
	for (ll &v : p) fin >> v, --v;
	for (ll &v : q) fin >> v, --v;
	
	fout << min(calc(p, q), calc(q, p)) << endl;
	
	return 0;
}
