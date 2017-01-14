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

void solve(int t) {
	cerr << "Starting case "<< t << endl;
	ll N, R;
	cin >> N >> R;
	
	vii zb(N, {-1, -1});
	vi Xs, Ys;
	for (ii &pr : zb) {
		cin >> pr.first >> pr.second;
		Xs.push_back(pr.first);
		Xs.push_back(pr.first+R);
		Ys.push_back(pr.second);
		Ys.push_back(pr.second+R);
	}
	
	sort(Xs.begin(), Xs.end());
	Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
	sort(Ys.begin(), Ys.end());
	Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());
	
	cerr << "Filtered duplicates" << endl;
	
	map<ll, ll> xmap, ymap;
	for (ll i = 0; i < ll(Xs.size()); ++i) xmap.insert({Xs[i], i});
	for (ll i = 0; i < ll(Ys.size()); ++i) ymap.insert({Ys[i], i});
	for (ii &pr : zb)
		pr.first = xmap[pr.first],
		pr.second = ymap[pr.second];
	
	cerr << "Mapped coords to [0..)" << endl;
	
	vi xpar(Xs.size(), -1LL), ypar(Ys.size(), -1LL);
	for (size_t i = 0; i < Xs.size(); ++i) {
		auto it = xmap.find(Xs[i]+R);
		if (it != xmap.end()) xpar[i] = it->second;
	}
	for (size_t i = 0; i < Ys.size(); ++i) {
		auto it = ymap.find(Ys[i]+R);
		if (it != ymap.end()) ypar[i] = it->second;
	}
	
	cerr << "Set parents" << endl;
	
	// O(N^3) calculate for each X,Y pair how many zombies
	// have xi <=/< X, yi <=/< Y.
	vvi eqeq(Xs.size(), vi(Ys.size(), 0LL));
	vvi eqlt(Xs.size(), vi(Ys.size(), 0LL));
	vvi lteq(Xs.size(), vi(Ys.size(), 0LL));
	vvi ltlt(Xs.size(), vi(Ys.size(), 0LL));
	for (ll X = 0; X < ll(xmap.size()); ++X)
	for (ll Y = 0; Y < ll(ymap.size()); ++Y) {
		ll s1 = 0LL, s2 = 0LL, s3 = 0LL, s4 = 0LL;
		for (ii pr : zb) {
			if (pr.first <= X && pr.second <= Y) ++s1;
			if (pr.first <  X && pr.second <= Y) ++s2;
			if (pr.first <= X && pr.second <  Y) ++s3;
			if (pr.first <  X && pr.second <  Y) ++s4;
		}
		eqeq[X][Y] = s1;
		lteq[X][Y] = s2;
		eqlt[X][Y] = s3;
		ltlt[X][Y] = s4;
	}
	
	cerr << "Computed square sums" << endl;
	
	// Loop over all squares in O(N^4).
	ll ans = 1LL;
	for (size_t x1 = 0; x1 < Xs.size(); ++x1)
	for (size_t y1 = 0; y1 < Ys.size(); ++y1) {
		if (xpar[x1] < 0 || ypar[y1] < 0) continue;
		ll val = 0LL;
		// Add everything in [x1, x1+R]*[y1, y1+R].
		val += eqeq[xpar[x1]][ypar[y1]];
		val -= eqlt[xpar[x1]][     y1 ];
		val -= lteq[     x1 ][ypar[y1]];
		val += ltlt[     x1 ][     y1 ];
		for (size_t x2 = 0; x2 < Xs.size(); ++x2)
		for (size_t y2 = 0; y2 < Ys.size(); ++y2) {
			if (xpar[x2] < 0 || ypar[y2] < 0) continue;
			ll val2 = 0LL;
			// Same for 2.
			val2 += eqeq[xpar[x2]][ypar[y2]];
			val2 -= eqlt[xpar[x2]][     y2 ];
			val2 -= lteq[     x2 ][ypar[y2]];
			val2 += ltlt[     x2 ][     y2 ];
			// Consider the intersection of the two squares.
			ll lx = max(x1, x2), rx = min(xpar[x1], xpar[x2]);
			ll ly = max(y1, y2), ry = min(ypar[y1], ypar[y2]);
			if (lx <= rx && ly <= ry) {
			// Subtract everything in this square, double counted.
				val2 -= eqeq[rx][ry];
				val2 += eqlt[rx][ly];
				val2 += lteq[lx][ry];
				val2 -= ltlt[lx][ly];
			}
			if (val+val2 > ans) ans = val+val2;
		}
	}
	cout << "Case #" << t << ": " << ans << '\n';
	cerr << "Case " << t << " is " << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
