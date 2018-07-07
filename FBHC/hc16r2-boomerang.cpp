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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void reverse(string &s) {
	for (int i = 0; i < int(s.length())/2; ++i)
		swap(s[i], s[int(s.length()) - 1 - i]);
}

void calcseg(vi &pref, vi &preff, string &L, string &R, int N) {
	vi nseg(N, -1);
	for (int i = 1; i < N; ++i) {
		if (R[i] == R[i - 1])	nseg[i] = nseg[i - 1];
		else			nseg[i] = i - 1;
	}
	
	pref.assign(N, 0);
	preff.assign(N, 0);
	pref[0] = (L[0] != R[0]);
	preff[0] = 1;
	for (int i = 1; i < N; ++i) {
		preff[i] = 1 + (nseg[i] >= 0 ? preff[nseg[i]] : 0);
		if (L[i] == R[i])
			pref[i] = pref[i - 1];
		else
			pref[i] = preff[i];
	}
}

void reversevi(vi &v) {
	for (int i = 0; i < int(v.size())/2; ++i)
		swap(v[i], v[int(v.size()) - 1 - i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		int N;
		cin >> N;
		string L, R;
		cin >> L >> R;
		
		vi pref, suff, preff, sufff;
		calcseg(pref, preff, L, R, N);
		reverse(L);
		reverse(R);
		calcseg(suff, sufff, L, R, N);
		reverse(L);
		reverse(R);
		reversevi(suff);
		
//		for (int i = 0; i < N; ++i)
//			cerr << pref[i] << ' ' << preff[i] << ' ' << suff[i]<<' '<<sufff[i] << endl;
		
		int ans = INF;
		if (L != R) {
			for (int i = 0; i <= N; ++i) {
				ans = min(ans, max((i>0?pref[i-1]:0), (i<N?suff[i]:0)));
			}
			int l = 0;
			while (l < N) {
				if (L[l] != R[l]) { l++; continue; }
				int r = l;
				while (r + 1 < N && L[r+1] == R[r+1]) ++r;
				ans = min(ans, max((l>0?pref[l-1]:0),(r<N-1?suff[r+1]:0)));
				l = r + 1;
			}
		} else ans = 0;
		cout << "Case #" << t << ": " << ans << endl;
	}
	
	return 0;
}
