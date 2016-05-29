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

pair<ll, ii> padd(pair<ll, ii> l, pair<ll, ii> r) {
	return {l.first+r.first, {l.second.first+r.second.first, l.second.second+r.second.second}};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int MAXN = 12;
	vector<vector<pair<ll, ii>>> by2(3, vector<pair<ll, ii>>(MAXN+1, {0LL, {0LL, 0LL}}));
	vector<vector<string>> lexo(3, vector<string>(MAXN+1, ""));
	// P=0,R=1,S=2, i beats i+1
	by2[0][0] = {1LL, {0LL, 0LL}};
	lexo[0][0] = "P";
	by2[1][0] = {0LL, {1LL, 0LL}};
	lexo[1][0] = "R";
	by2[2][0] = {0LL, {0LL, 1LL}};
	lexo[2][0] = "S";
	
	for (int n = 1; n <= MAXN; ++n) {
		for (int i = 0; i < 3; ++i) {
			by2[i][n] = padd(by2[i][n-1], by2[(i+1)%3][n-1]);
			string &l = lexo[i][n-1];
			string &r = lexo[(i+1)%3][n-1];
			lexo[i][n] = (l<r ? l+r : r+l);
		}
	}
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		
		int R, P, S, N;
		cin >> N >> R >> P >> S;
		
		bool pos = false;
		string mn = "";
		for (int i = 0; i < 3; ++i) {
			if (P == by2[i][N].first
			 && R == by2[i][N].second.first
			 && S == by2[i][N].second.second) {
				if (pos) mn = min(mn, lexo[i][N]);
				else { pos = true; mn = lexo[i][N]; }
			}
		}
		if (pos) cout << "Case #" << t << ": " << mn << '\n';
		else cout << "Case #" << t << ": IMPOSSIBLE\n";
	}
	
	return 0;
}
