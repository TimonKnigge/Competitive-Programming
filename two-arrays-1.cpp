#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
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

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;

constexpr ll MOD = 1000000007;

#define mod(v) ((v) % MOD)

struct Node {
	int li = 0, ri = 0;
	int fullsum = 0, asum = 0, bsum = 0;
	int lc = -1, rc = -1;
	int alazy = 0, blazy = 0;
};
vector<Node> tr;
void build(int ix, int l, int r) {
	tr[ix].li = l; tr[ix].ri = r;
	if (l < r) {
		tr[ix].lc = tr.size();
		tr[ix].rc = tr.size() + 1;
		tr.push_back(Node());
		tr.push_back(Node());
		int m = (l + r) / 2;
		build(tr[ix].lc, l, m);
		build(tr[ix].rc, m + 1, r);
	}
}
void propagate(int ix) {
	if (tr[ix].alazy == 0 && tr[ix].blazy == 0) return;
	int L = tr[ix].lc, R = tr[ix].rc;
	tr[L].alazy = mod(tr[L].alazy + tr[ix].alazy);
	tr[L].asum = mod(mod(tr[ix].alazy * (r - l + 1)) + tr[L].asum);
	tr[L].fullsum += 
}
void update(

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	tr.push_back(Node());
	build(0, 0, N - 1);
	
	
	
	return 0;
}
