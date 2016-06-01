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
#include "rps.h"

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

using ci = pair<char, int>;
inline ci op(ci l, ci r) {
	if (l.first == r.first) return l;
	if (l.first == 'R' && r.first == 'P') return r;
	if (l.first == 'P' && r.first == 'S') return r;
	if (l.first == 'S' && r.first == 'R') return r;
	return l;
}

constexpr int MASTER = 0;

ci recurse(int ln, int rn, ci myci) {
	if (ln == rn) {
		if (ln == 0) return myci;
		else
		Receive(ln);
		ll rid = GetLL(ln);
		return {GetFavoriteMove(rid), rid};
	} else {
		ci lv = recurse(ln, (ln+rn)/2, myci);
		ci rv = recurse((ln+rn)/2+1, rn, myci);
		return op(lv, rv);
	}
}

int main() {
	
	int N = GetN();
	int nodes = NumberOfNodes();
	int id = MyNodeId();
	
	ll NN = 1LL<<N;
	
	if (nodes > NN) {
		if (id != MASTER) return 0;
		
		vector<ci> myv(NN, {'R', -1});
		for (ll i = 0LL; i < NN; ++i) myv[i] = {GetFavoriteMove(i), i};
		
		for (ll c = 1; c < NN; c <<= 1)
			for (ll i = 0LL; i < NN; i += (c<<1))
				myv[i] = op(myv[i], myv[i+c]);
	
		cout << myv[0].second << endl;
		return 0;
	}
	
	ll L = 0LL, R = 0LL;
	if (id == MASTER) {
		queue<pair<ii, ii>> q;
		vii resp(nodes, {0LL, 0LL});
		q.push({{0, NN}, {0, nodes-1}});
		while (!q.empty()) {
			ii rn = q.front().first;
			ii nds = q.front().second;
			q.pop();
			
			if (nds.first == nds.second) {
				resp[nds.first] = rn;
				continue;
			}
			ll m = (nds.first+nds.second)/2LL;
			ll rm = rn.first + (rn.second-rn.first)/2LL;
			q.push({{rn.first, rm}, {nds.first, m}});
			q.push({{rm, rn.second}, {m+1, nds.second}});
		}
		for (int n = 1; n < nodes; ++n) {
			PutLL(n, resp[n].first);
			PutLL(n, resp[n].second);
			Send(n);
		}
		L = resp[0].first;
		R = resp[0].second;
	} else {
		Receive(0);
		L = GetLL(0);
		R = GetLL(0);
	}
	
//	cerr << id << ' ' << L << ' ' <<R << endl;
	
	vector<ci> myv(R-L, {'R', -1});
	for (ll i = L; i < R; ++i) myv[i-L] = {GetFavoriteMove(i), i};
	
	for (ll c = 1; c < R-L; c <<= 1)
		for (ll i = L; i < R; i += (c<<1))
			myv[i-L] = op(myv[i-L], myv[i-L+c]);

//	cerr << id << " got " << myv[0].first << ' ' << myv[0].second << endl;

	if (id == MASTER) {
		ci ans = recurse(0, nodes-1, myv[0]);
		cout << ans.second << endl;
	} else {
		PutLL(MASTER, myv[0].second);
		Send(MASTER);
	}
	
	return 0;
}
