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
using llll = pair<ll, ll>;
const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

llll do_or(llll l, llll r) {
	return {l.first|r.first,l.second|r.second};
}

bool solve(int i, int N, int j, int s, llll msk, vector<llll> &bm, vi &sol) {
	if (j == s) {
		int c = __builtin_popcountll(msk.first)
			+ __builtin_popcountll(msk.second);
		return (c == N);
	}
	if (i == -1) return false;
	// use or don't use i
	sol.push_back(i);
	if (solve(i-1, N, j+1, s, do_or(msk, bm[i]), bm, sol))
		return true;
	sol.pop_back();
	return solve(i-1, N, j, s, msk, bm, sol);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, tcase = 0;
	while (cin >> N) {
		++tcase;
		vector<vb> B(N, vb(N, false));
		vector<llll> bm(N, {0LL, 0LL});
		for (int i = 0; i < N; ++i) {
			string ss;
			cin >> ss;
			for (int j = 0; j < N; ++j)
				B[i][j] = ss[j] == '1';
			B[i][i] = true;
			
			for (int j = 0; j < min(60, N); ++j) {
				if (B[i][j]) bm[i].first |= (1LL<<j);
			}
			for (int j = 60; j < N; ++j) {
				if (B[i][j]) bm[i].second |= (1LL<<(j-60));
			}
		}
		
		// Try finding groups of size 1..6
		vi sol;
		bool f = false;
		for (int s = 1; !f && s <= 6; ++s) {
			if (solve(N - 1, N, 0, s, {0LL, 0LL}, bm, sol))
				f = true;
		}
		
		if (!f) { // greedy 7
			vb taken(N, false);
			for (int r = 1; r <= 7; ++r) {
				int sz = 0, id = -1;
				for (int i = 0; i < N; ++i) {
					int this_sz = 0;
					for (int j = 0; j < N; ++j) {
						if (B[i][j] && !taken[j])
							++this_sz;
					}
					if (this_sz > sz) {
						sz = this_sz;
						id = i;
					}
				}
				sol.push_back(id);
				for (int i = 0; i < N; ++i)
					if (B[id][i]) taken[i] = true;
			}
		}
		
		cout << "Case " << tcase << ": " << sol.size();
		for (int i = 0; i < sol.size(); ++i) {
			cout << " " << 1+sol[i];
		}
		cout << endl;
	}
	
	return 0;
}
