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

int findl(int l) {
	if (l % 2 == 0) --l;
	return l;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		
		bool adj[26][26];
		for (int i = 0; i < 26; ++i)
			for (int j = 0; j < 26; ++j)
				adj[i][j] = true;
		while (N--) {
			string s;
			cin >> s;
			adj[s[0]-'a'][s[1]-'a'] = false;
		}
		
		bool pos[26][39];
		int  par[26][39];
		for (int c = 0; c < 26; ++c) {
			pos[c][0] = true;
			par[c][0] = -1;
		}
		for (int l = 0; l < 38; ++l) {
			for (int c = 0; c < 26; ++c)
				pos[c][l+1] = false;
			for (int c = 0; c < 26; ++c) {
				if (!pos[c][l]) continue;
				for (int c2 = 0; c2 < 26; ++c2) {
					if (!adj[c][c2]) continue;
					pos[c2][l+1] = true;
					par[c2][l+1] = c;
				}
			}
		}
		
		int optc = 0, optl = 0;
		for (int l = 1; l < 39; ++l)
			for (int c = 0; c < 26; ++c) {
				if (pos[c][l] && l > optl) {
					optc = c;
					optl = l;
					break;
				}
			}
		
		int L = findl(optl + 1);
		vector<char> sol(L, ' ');
		for (int i = L - 1; i >= 0; --i) {
			sol[i] = char(int('a') + optc);
			optc = par[optc][optl];
			--optl;
		}
		int W = (L + 1) / 2;
		for (int r = 0; r < W; ++r) {
			for (int c = 0; c < W; ++c)
				cout << sol[r+c];
			cout << '\n';
		}
		cout << flush;
	}
	
	return 0;
}
