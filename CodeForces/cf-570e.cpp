#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

void printcor(int x, int y) { cout << '(' << x << ',' << y << ')'; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<char> > board(m, vector<char>(n, ' '));
	for (int j = 0; j < n; ++j) {
		string s; cin >> s;
		for (int i = 0; i < m; ++i)
			board[i][j] = s[i];
	}
	
	vector< vector< vector<ll> > >
		dp(2, vector< vector<ll> >(m, vector<ll>(m, 0)));
	dp[0][0][0] = (board[0][0] == board[m - 1][n - 1]);
	ll ans = 0LL;
	for (int l = 0; l < (n + m) / 2 - 1; ++l) {
		dp[(l+1)%2].assign(m, vector<ll>(m, 0));
		for (int lx = 0; lx < m; ++lx) {
 			for (int _rx = 0; _rx < m; ++_rx) {
				int ly = l - lx, rx = m - 1 - _rx;
				int ry = n - 1 - (l - _rx);
				if (lx < 0 || rx < 0 || lx >= m || rx >= m
				 || ly < 0 || ry < 0 || ly >= n || ry >= n)
					continue;
				if (board[lx][ly] != board[rx][ry])
					continue;

//				cout << '(' << lx << ',' << ly << ") (" << rx << ','  << ry << ')' << endl;

				for (int dlx = 0, dly = 1; dlx < 2; ++dlx, --dly) {
				for (int drx = 0, dry = 1; drx < 2; ++drx, --dry) {
					if (rx - drx < 0 || ry - dry < 0
					 || lx + dlx >= m || ly + dly >= n)
						continue;
					if (board[lx+dlx][ly+dly]
					 != board[rx-drx][ry-dry]) continue;
					
					ll add = dp[l % 2][lx][_rx];

//					printcor(lx, ly);
//					cout << " and ";
//					printcor(rx, ry);
//					cout << " to ";
//					printcor(lx+dlx, ly+dly);
//					cout << " and ";
//					printcor(rx-drx, ry-dry);
//					cout << " => " << add << endl;

					if (l < (n + m) / 2 - 2) {
						dp[(l+1)%2][lx+dlx][_rx+drx] += add;
						dp[(l+1)%2][lx+dlx][_rx+drx] %= MOD;
					} else {
						if ((n + m) % 2 == 0) {
							if (rx - drx == lx + dlx
							 && ry - dry == ly + dly) {
								ans += add;
								ans %= MOD;
							}
						} else {
							if (abs(rx - drx - lx - dlx) + abs(ry - dry - ly - dly) == 1) {
								ans += add;
								ans %= MOD;
							}
						}
					}
				}}
			}
		}
	}

	cout << ans << endl;
	
	return 0;
}
