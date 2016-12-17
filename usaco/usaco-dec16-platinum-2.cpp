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

constexpr ll MOD = 1e9+9;

template <class T>
struct FenwickTree {		// use 1 based indices!!!
	int n; vector<T> tree;
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return (MOD + query(r) - query(l - 1)) % MOD; }
	T query(int r) {
		T s = 0;
		for(; r > 0; r -= (r & (-r))) s = (s + tree[r]) % MOD;
		return s;
	}
	void update(int i, T v) {
		for(; i <= n; i += (i & (-i))) tree[i] = (tree[i] + v) % MOD;
	}
	void reset() { tree.assign(tree.size(), 0LL); }
};

int main() {
	ifstream fin("team.in");
	
	int N, M, K;
	fin >> N >> M >> K;
	vi FJ(N, 0LL), FP(M, 0LL);
	for (ll &v : FJ) fin >> v;
	for (ll &v : FP) fin >> v;
	fin.close();
	
	sort(FJ.begin(), FJ.end());
	sort(FP.begin(), FP.end());
	
	// dp[cows picked][first av fj][first av fp]
	vector<FenwickTree<ll>> fts(K-1, FenwickTree<ll>(N + 5LL));
	ll ans = 0LL;
	for (int j = 0; j < M; ++j) {
		for (int c = K; c > 0; --c) {
			for (int i = N - 1; i >= c-1; -- i) {
				// exactly c cows, with i,j the last
				if (FJ[i] <= FP[j]) continue; 
				ll v = (c > 1LL ? fts[c-2].query(i) : 1LL);
				if (c < K)
					fts[c-1].update(i+1, v);
				else	ans = (ans + v) % MOD;
			}
		}
	}
	
	ofstream fout("team.out");
	fout << ans << endl;
	fout.close();
	
	return 0;
}
