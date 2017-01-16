// Greedy solution, WA on 2/12 cases.
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
using namespace chrono;
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

using T = pair<ld, ll>;
T ident = {1e100, -1LL};
T op(T l, T r) {
	return min(l, r);
}
struct SegmentTree {
	int n; vector<T> tree;
	SegmentTree(int _n) : n(_n), tree(2 * n, ident) { }
	void update(int i, T val) {
		for (tree[i+n] = val, i = (i+n)/2; i > 0; i /= 2)
			tree[i] = op(tree[2*i], tree[2*i+1]);
	}
	T query(int l, int r) {
		T lhs = T(ident), rhs = T(ident);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (  l&1 ) lhs = op(lhs, tree[l++]);
			if (!(r&1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

int main() {
	auto beg = high_resolution_clock::now();
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream fin("tallbarn.in");
	
	ll N, K;
	fin >> N >> K;
	
	vi A(N, 0LL), has(N, 0LL);
	for (int i = 0; i < N; ++i) {
		fin >> A[i];
	}
	sort(A.rbegin(), A.rend());
	
	ll S = accumulate(A.begin(), A.end(), 0LL);

	for (int i = 0; i < N; ++i) {
		has[i] = ll(ld(K) * ld(A[i]) / ld(S));
	}
	K -= accumulate(has.begin(), has.end(), 0LL);
	for (int i = 0; i < N; ++i) {
		has[i] += K / N;
		if (i < K%N) ++has[i];
	}
	
	SegmentTree remtree(N);
	SegmentTree addtree(N);

	for (ll i = 0; i < N; ++i) {
		ld rem = ld(-A[i]) / ld(has[i]) / ld(has[i]+1);
		remtree.update(i, {rem, i});
		if (has[i] > 1) {
			ld add = ld( A[i]) / ld(has[i]) / ld(has[i]-1);
			addtree.update(i, {add, i});
		}
	}
	
	while(high_resolution_clock::now() - beg <
		milliseconds(1900)) {
		pair<ld, ll> rem = remtree.query(0, N-1);
		pair<ld, ll> add = addtree.query(0, N-1);
		if (rem.first + add.first >= 0) break;
		
		ll r = rem.second;
		ll a = add.second;
		
		ll ls = 1, rs = has[a] - 1;
		while (rs - ls > 5) {
			ll lls = (ls+ls+rs)/3;
			ll rrs = (ls+rs+rs)/3;
			ld llv = ld(A[r]) / ld(has[r]+lls) + ld(A[a]) / ld(has[a]-lls);
			ld rrv = ld(A[r]) / ld(has[r]+rrs) + ld(A[a]) / ld(has[a]-rrs);
			if (llv < rrv)
				rs = rrs;
			else	ls = lls;
		}
		pair<ld, ll> bestx = {ld(A[r]) / ld(has[r]+rs) + ld(A[a]) / ld(has[a]-rs), rs};
		for (ll i = ls; i < rs; ++i) {
			pair<ld, ll> thisx = {ld(A[r]) / ld(has[r]+i) + ld(A[a]) / ld(has[a]-i), i};
			bestx = min(bestx, thisx);
		}
		
		has[r] += bestx.second;
		has[a] -= bestx.second;
		remtree.update(r, make_pair(ld(-A[r]) / ld(has[r]) / ld(has[r]+1), r));
		addtree.update(r, make_pair(ld( A[r]) / ld(has[r]) / ld(has[r]-1), r));
		remtree.update(a, make_pair(ld(-A[a]) / ld(has[a]) / ld(has[a]+1), a));
		if (has[a] > 1)
			addtree.update(a, make_pair(ld( A[a]) / ld(has[a]) / ld(has[a]-1), a));
		else	addtree.update(a, ident);
	}
	
	ld sum = 0.0;
	for (int i = 0; i < N; ++i)
		sum += ld(A[i]) / ld(has[i]);
	ofstream fout("tallbarn.out");
	fout << ll(sum + 0.58) << endl;
	
	return 0;
}
