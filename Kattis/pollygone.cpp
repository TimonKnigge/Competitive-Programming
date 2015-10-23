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
const ll LLINF = 9000000000000000000LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N >> ws;
	
	long double ldP;
	cin >> ldP;
	ll P = ll(10000 * ldP + 0.5);
	
	vector<ll> minimal(10001, LLINF);
	minimal[0] = 0;
	
	ll upp = 0;
	for (int i = 0; i < N; ++i) {
		int e;
		cin >> e >> ws;
		cin >> ldP;
		ll p = ll(10000 * ldP + 0.5);
		
		for (ll pr = upp; pr >= 0; --pr) {
			if (minimal[pr] == LLINF) continue;
			if (minimal[pr] + e < minimal[pr + p]) {
				minimal[pr + p] = minimal[pr] + e;
				if (upp < pr + p) upp = pr + p;
			}
		}
	}
	
	ll least = LLINF;
	for (int i = P; i <= 10000; ++i)
		if (least > minimal[i]) least = minimal[i];
	cout << least << endl;
	
	return 0;
}
