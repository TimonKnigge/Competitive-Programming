/*
	NOTE: WA on 2/36 cases ..
*/

#include <iostream> 
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
#include <cstdio>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<ll> t(N, 0);
	vi unr;
	vb isunr(N, false);
	vector<ll> hv, hv2;
	set<int> mark;
	hv.push_back(1); hv.push_back(1e9);
	mark.insert(1); mark.insert(1e9);
	for (int i = 0; i < N; ++i) {
		int ti;
		scanf("%d", &ti);
		t[i] = ti;
		if (ti == 0) {
			unr.push_back(i);
			isunr[i] = true;
		} else {
			hv2.push_back(ti);
			if (mark.find(ti) == mark.end()) {
				mark.insert(ti);
				hv.push_back(ti);
			}
		}
	}
	sort(hv.begin(), hv.end());
	if (hv2.size() == 0) hv2.push_back(5e8);
	sort(hv2.begin(), hv2.end());
	vii comm;
	for (int i = 0; i < N; ++i) {
		if (i == 0 || hv2[i - 1] != hv2[i])
			comm.push_back({1, hv2[i]});
		else comm.back().first++;
	}
	sort(comm.begin(), comm.end());

	const int TC = 4;
	const int SZ = 1 << (3*TC);
	// The zero-shift gives score 0.
	vi optimal[SZ];
	ll optv[SZ];
	for (int i = 0; i < SZ; ++i) { optv[i] = -1LL; }
	for (int k = 0; k < N ; ++k) {
		ll score = 0LL;
		
		// First compute the readable distance
		for (int i = 0; i < N; ++i) {
			if (isunr[i] || isunr[(i+k)%N]) continue;
			score += abs(t[i] - t[(i+k)%N]);
		}
		
		// Consider each {1, 1e9} assignment of the unreadable values
		if (unr.size() > 0) {
			for (int msk = 0; msk < (1<<(unr.size()*TC)); ++msk) {
				ll thisscore = 0LL;
				for (int i = 0; i < unr.size(); ++i) {
					int sh = ((msk>>(TC*i))&((1<<TC)-1));
					if ((sh&3)==0) {
						sh /= 4;
						t[unr[i]] = hv[min(sh, int(hv.size()) - 1)];
					} else if ((sh&3)==1) {
						sh /= 4;
						t[unr[i]] = hv[max(0, int(hv.size()) - 1 - sh)];
					} else if ((sh&3)==2) {
						sh /= 4;
						int sz = int(hv.size());
						int idx = sz/2+sh - 4;
						t[unr[i]] = hv[max(0, min(sz - 1, idx))];
					} else if ((sh&3)==3) {
						sh /= 4;
						int idx = int(comm.size()) - 1 - sh;
						t[unr[i]] = comm[max(0, idx)].second;
					}
//					t[unr[i]] = (((msk>>i)&1)==1 ? 1e9 : 1);
				}
				for (int i : unr) {
					// Top to bottom:
					thisscore += abs(t[i] - t[(i+k)%N]);
					if (!isunr[(i+N-k)%N]) {
						thisscore += abs(t[i] - 
							t[(i+N-k)%N]);
					}
				}
				if (score + thisscore > optv[msk]) {
					optv[msk] = score + thisscore;
					optimal[msk].clear();
					optimal[msk].push_back(k);
				} else if (score + thisscore == optv[msk]) {
					optimal[msk].push_back(k);
				}
			}
			for (int i : unr) t[i] = 0;
		} else {
			if (score > optv[0]) {
				optv[0] = score;
				optimal[0].clear();
				optimal[0].push_back(k);
			} else if (score == optv[0]) {
				optimal[0].push_back(k);
			}
		}
		
//		if (score > optv) {
//			optv = score;
//			optimal.clear();
//			optimal.push_back(k);
//		} else if (score == optv) {
//			optimal.push_back(k);
//		}
	}
	
	vb isopt(N, false);
	for (int j = 0; j < SZ; ++j) {
	for (int i : optimal[j]) isopt[i] = true; 
	}
//	bool zerorot = true; int v = -1;
//	for (int i = 0; i < N; ++i) {
//		if (isunr[i]) continue;
//		if (v == -1) v = t[i];
//		else zerorot = zerorot && v == t[i];
//	}
//	if (zerorot) isopt[0] = true;
	
	vi outp;
	for (int i = 0; i < N; ++i) if (isopt[i]) outp.push_back(i);
	
	cout << outp.size() << endl;
	cout << outp[0];
	for (int i = 1; i < outp.size(); ++i) cout << ' ' << outp[i];
	cout << endl;
	
	return 0;
}
