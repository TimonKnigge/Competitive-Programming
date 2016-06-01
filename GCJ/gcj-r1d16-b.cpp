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
#include "oops.h"

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

int main() {
	
	ll N = GetN();
	ll nodes = NumberOfNodes();
	ll id = MyNodeId();
	
	ll per = N / nodes, spec = N%nodes;
	ll l = id * per + min(spec, id);
	ll r = l + per + (id < spec ? 1LL : 0LL);

//	cout << id << ' ' << l << ' ' <<r << endl;

	ll mn = GetNumber(l), mx = GetNumber(l);
	for (; l < r; ++l) {
		ll no = GetNumber(l);
		if (no < mn) mn = no;
		if (mx < no) mx = no;
	}

//	cerr << id << ' '<< mn << ' ' << mx << endl;

	if (id == 0LL) {
		for (int n = 1; n < nodes; ++n) {
			Receive(n);
			mn = min(mn, GetLL(n));
			mx = max(mx, GetLL(n));
		}
		cout << (mx-mn) << endl;
	} else {
		PutLL(0, mn);
		PutLL(0, mx);
		Send(0);
	}
	
	return 0;
}
