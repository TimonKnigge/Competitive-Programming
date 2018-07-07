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

map<ll, size_t> table_loc;
ld t[6][20][401];

void precompute_tables() {
	vi Ys = {4,6,8,10,12,20};
	ll Xmax = 20LL;
	for (ll y : Ys) {
		ld frac = 1.0 / ld(y);
		size_t id = table_loc.size();
		table_loc.insert({y, id});
		for (ll v = 1LL; v <= y; ++v)
			t[id][0][v] = frac;
		t[id][0][0] = 0.0;
		for (ll i = y + 1; i <= 400; ++i) t[id][0][i] = 0.0;
		for (ll w = 0LL; w < Xmax - 1LL; ++w) {
			for (ll i = 400LL; i >= 0LL; --i) {
				t[id][w+1][i] = 0.0;
				for (ll v = 1LL; v <= y; ++v) {
					if (i+v > 400LL) break;
					t[id][w+1][i+v] += frac*t[id][w][i];
				}
				if (i < 400LL) t[id][w][i] += t[id][w][i+1];
			}
			for (ll i = 400LL; i >= 0LL; --i)
				t[id][w][i] /= t[id][w][0];
		}
	}
}

double f() {
	int H, S;
	scanf("%d %d", &H, &S);
	
	ld best = 0.0;
	for (ll i = 0LL; i < S; ++i) {
		int X, Y, Z = 0;
		char c, s;
		scanf("%d%c%d%c", &X, &c, &Y, &s);
		if (s == '-' || s == '+') {
			scanf("%d", &Z);
			if (s == '-') Z = -Z;
		}
//		cerr << "Got: " << X << ' ' << Y << ' ' << Z << '\n';
		
		size_t tid = table_loc[Y];
		int lb = max(0, min(400, H - Z));
		if (best < t[tid][X-1][lb])
			best = t[tid][X-1][lb];
	}
	return double(best);
}

int main() {
	precompute_tables();
	
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; ++t)
		printf("Case #%d: %.10lf\n", t, f());
	
	return 0;
}
