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

#include "message.h"
#include "crates.h"

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

// NumberOfNodes()
// MyNodeId()
// Put[Int/LL/Char](id, val)
// Send(id)
// Receive(id)
// Get[Int/LL/Char](id)

ll rsum(vi &v, ll l, ll r) {
	l = max(0LL, l);
	r = min(r, ll(v.size()) - 1LL);
	if (l > r) return 0LL;
	ll ret = v[r];
	if (l > 0) ret -= v[l-1];
	return ret;
}

constexpr ll MOD = 1e9+7;

int main() {
	
	ll nodes = NumberOfNodes();
	ll id = MyNodeId();
	ll N = GetNumStacks();
	
	if (id >= N) return 0;
	nodes = min(N, nodes);
	
	// My intv
	ll per = N/nodes, spec = N%nodes;
	ll L = id*per + min(id, spec);
	ll R = L + per + (id<spec?1LL:0LL);
	
//	if (id == 0) cerr << N << " stacks" << endl;
//	cerr << id << ' ' << L << ' ' <<R << endl;
	
	// Find the number of crates
	ll crates = 0LL;
	vector<int> mcrates(R-L, 0);
	for (ll i = L; i < R; ++i)
		mcrates[i-L] = GetStackHeight(i+1),
		crates += ll(mcrates[i-L]);
	
	ll totalcrates = 0LL;
	ll req = 0LL;
	ll leftside = 0LL, rightside = 0LL;
	if (id == 0) {
		vi node_crates(nodes, 0LL);
		node_crates[0] = crates;
		totalcrates += crates;
		for (int n = 1; n < nodes; ++n) {
			Receive(n);
			node_crates[n] = GetLL(n);
			totalcrates += node_crates[n];
		}
		
		vi shouldhave(nodes, 0LL);
		ll _l = L, _r = R, rem = totalcrates%N;
		for (int n = 0; n < nodes; ++n) {
			shouldhave[n] = (_r-_l) * (totalcrates/N);
			shouldhave[n] += min(_r-_l, rem);
			rem = max(0LL, rem - (_r-_l));
//			cerr << n << ' ' << _l << ' ' <<_r << " !"<<endl;
			_l = _r;
			_r = _l + per + (n+1<spec?1LL:0LL);
		}
//		cerr << totalcrates << " crates in total" << endl;
//		for (int n = 0; n < nodes; ++n)
//			cerr << n << " should have " << shouldhave[n] << " crates" << endl;
		
		vi node_crates_prefix(nodes, 0LL);
		vi shouldhave_prefix(nodes, 0LL);
		for (int n = 0; n < nodes; ++n) {
			node_crates_prefix[n] = node_crates[n]
				+ (n>0 ? node_crates_prefix[n-1] : 0LL);
			shouldhave_prefix[n] = shouldhave[n]
				+ (n>0 ? shouldhave_prefix[n-1] : 0LL);
		}
		
		rightside = rsum(node_crates_prefix, 1, nodes-1)
			  - rsum(shouldhave_prefix, 1, nodes-1);
		req = shouldhave[0];
		for (int n = 1; n < nodes; ++n) {
			PutLL(n, totalcrates);
			PutLL(n, shouldhave[n]);
			PutLL(n,
				rsum(node_crates_prefix, 0, n-1)
				- rsum(shouldhave_prefix, 0, n-1));
			PutLL(n,
				rsum(node_crates_prefix, n+1, nodes-1)
				- rsum(shouldhave_prefix, n+1, nodes-1));
			Send(n);
		}
	} else {
		PutLL(0, crates);
		Send(0);
		Receive(0);
		totalcrates = GetLL(0);
		req = GetLL(0);
		leftside = GetLL(0);
		rightside = GetLL(0);
	}
	
	/*	totalcrates: total # crates
		crates: our # crates
		req: our wanted #crates
		leftside: profit/deficit left
		rightside: profit/deficit right
	*/
//	cerr << id << ' ' << leftside << ' '<<rightside << endl;
	
	//vector<int> mcrates(R-L, 0);
	vector<int> mreq(R-L, 0);
	ll ivcrates = totalcrates/N;
	ll rem = totalcrates%N;
	ll _l = 0, _r = per + (spec>0?1LL:0LL);
	for (int n = 0; n < id; ++n) {
		rem = max(0LL, rem - (_r - _l));
		_l = _r;
		_r = _l + per + (n+1<spec?1LL:0LL);
	}
	for (ll i = L; i < R; ++i) {
		mreq[i-L] = ivcrates;
		if (rem>0) mreq[i-L]++, rem--;
//		cerr << "mreq["<<i-L<<"] = " <<mreq[i-L] << endl;
	}
	
	ll cost = 0LL;
	for (ll i = 0; i < (R-L); ++i) {
		leftside += ll(mcrates[i]) - ll(mreq[i]);
		cost = (cost + abs(leftside)%MOD + MOD) % MOD;
	}
//	cerr << id << " gives cost " << cost << endl;
	
	if (id == 0) {
		for (int n = 1; n < nodes; ++n) {
			Receive(n);
			cost = (cost + GetLL(n) + MOD) % MOD;
		}
		cout << cost << endl;
	} else {
		PutLL(0, cost);
		Send(0);
	}
	
	return 0;
}
