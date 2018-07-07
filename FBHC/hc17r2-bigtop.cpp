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

void recompute(vector<ld> &myarr, ld &cur, map<ll, ll> &poles,
		vi &X, vi &H, int N, int i) {
	// Recompute i
	auto it = poles.find(X[i]);
	if (it == poles.end()) {
		cerr << "Problem.." << endl;
		return;
	}
	cur -= myarr[i];
	
	auto itl = it, itr = it;
	if (itl != poles.begin())
		--itl;
	else	itl = poles.end();
	itr++;
	
	int l = (itl != poles.end() ? itl->second : -1);
	int r = (itr != poles.end() ? itr->second : -1);
//	cerr << "Recomputing for " << i << ", has " << l << ',' << r << " as neighbours" << endl;
	myarr[i] = H[i] * H[i];
	
	ld li = (l == -1 ? 0.0l : 
		max(0.0l, ld(H[l] - H[i] + X[i] + X[l])/2.0 - ld(X[i]-H[i])));
	ld ri = (r == -1 ? 0.0l :
		max(0.0l, ld(X[i]+H[i]) - ld(H[i] - H[r] + X[r] + X[i])/2.0));
//	cerr << "Got " << li << " and " << ri << endl;
	myarr[i] -= (li * li + ri * ri) / 2.0;
	if (myarr[i] < 0) myarr[i] = 0;
	
	cur += myarr[i];
}

void solve(int t) {
	cerr << t << endl;
	int N;
	cin >> N;
	
	vi X(N, 0LL), H(N, 0LL);
	ll Ax, Bx, Cx, Ah, Bh, Ch;
	cin >> X[0] >> Ax >> Bx >> Cx;
	cin >> H[0] >> Ah >> Bh >> Ch;
	
	for (int i = 1; i < N; ++i)
		X[i] = (X[i - 1] * Ax + Bx) % Cx + 1LL,
		H[i] = (H[i - 1] * Ah + Bh) % Ch + 1LL;
//	for (int i = 0; i < N; ++i)
//		cerr << ' ' << X[i] << ' ' <<H[i] << endl;
	
	ld ans = H[0] * H[0], cur = H[0] * H[0];
	map<ll, ll> poles;
	poles.insert({X[0], 0LL});
	vector<ld> myarr(N, 0.0);
	myarr[0] = cur;
	
	for (int i = 1; i < N; ++i) {
//		cerr << "Doing " << i << endl;
		auto itr = poles.lower_bound(X[i]);
		auto itl = poles.lower_bound(X[i]);
		if (itl != poles.begin())
			itl--;
		else	itl = poles.end();
		
		int l = -1, r = -1;
		if (itl != poles.end()) l = itl->second;
		if (itr != poles.end()) r = itr->second;
		
		// If they exist, itl and itr are the neighbouring
		// poles of i.
		// Is i covered by any of these poles?
		if (l != -1 && H[l] - (X[i] - X[l]) >= H[i]) {
			ans += cur;
			continue;
		}
		if (r != -1 && H[r] - (X[r] - X[i]) >= H[i]) {
			ans += cur;
			continue;
		}
//		cerr << "Done sweeping, got " << l << ' ' << r << endl;
		
		// Start removing things we cover.
		while (l != -1 && H[i] - (X[i] - X[l]) >= H[l]) {
			poles.erase(itl);
			cur -= myarr[l];
			itl = poles.lower_bound(X[i]);
			if (itl != poles.begin()) --itl;
			if (itl == poles.end() || itl->first > X[i]) {
				itl = poles.end();
				l = -1;
			} else	l = itl->second;
		}
		while (r != -1 && H[i] - (X[r] - X[i]) >= H[r]) {
			poles.erase(itr);
			cur -= myarr[r];
			itr = poles.lower_bound(X[i]);
			if (itr == poles.end() || itr->first < X[i]) {
				itr = poles.end();
				r = -1;
			} else	r = itr->second;
		}
//		cerr << "Done covering, now with " << l << ' ' << r<< endl;
		// l, r are the next neighbours we have.
		poles.insert({X[i], i});
		recompute(myarr, cur, poles, X, H, N, i);
		if (l != -1)
			recompute(myarr, cur, poles, X, H, N, l);
		if (r != -1)
			recompute(myarr, cur, poles, X, H, N, r);
//		cerr << "Done recomputing" << endl;
//		cerr << "Now: " << cur << endl;
		ans += cur;
	}
	printf("Case #%d: %.10lf\n", t, double(ans));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	
	return 0;
}
