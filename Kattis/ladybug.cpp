#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

typedef pair<int, int> ii;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	while (cin >> s) {
		if (s.length() == 0) continue;
		int N;
		cin >> N;
		
		vector<bool> hasdigit(10, false);
		bool plus = false, minus = false, times = false, divides = false, equals = false;
		for (size_t i = 0; i < s.length(); ++i) {
			char c = s[i];
			if (c >= '0' && c <= '9') {
				hasdigit[c - '0'] = true;
			}
			else switch (c) {
				case '+': plus    = true; break;
				case '-': minus   = true; break;
				case '*': times   = true; break;
				case '/': divides = true; break;
				case '=': equals  = true; break;
				default : 		  break;
			}
		}
		bool anyforce = plus || minus || times || divides || equals;
		
		vector<int> nct(1000, 0);
		nct[0] = hasdigit[0] ? 1 : -1;
		for (int i = 1; i < 1000; ++i) {
			int j = i, tp = 0;
			while (j > 0 && tp >= 0) {
				if (!hasdigit[j % 10]) {
					tp = -1;
				} else {
					tp++;
					j /= 10;
				}
			}
			nct[i] = tp;
		}

		if (!anyforce && nct[N] <= 0) {
			if (N == 0) cout << 0 << endl;
			else cout << "impossible" << endl;
			continue;
		}
		
		priority_queue<ii, vector<ii>, greater<ii> > pq;
		vector<int> dist(1000, 1e8), dispcost(1000, 1e8);
		dist[0] = 0; dispcost[0] = 0;
		pq.push({0, 0});
		for (int i = 1; i < 1000; ++i) {
			if (nct[i] == -1) continue;
			dist[i] = dispcost[i] = nct[i];
			pq.push({dist[i], i});
		}
		// plus minus times divides equals anyforce
		
		while (!pq.empty()) {
			int u = pq.top().second, w = pq.top().first; pq.pop();
//cerr << "Got " << u << " at cost " << w << endl;
			if (w > dist[u]) continue;
			if (u == N) break;
			// Try expanding: double operator
			if (plus && equals && 2 * u < 1000 && u != 0) {
				int nc = w + 2;
				if (nc < dist[2 * u]) {
					dist[2 * u] = nc;
					pq.push({nc, 2 * u});
				}
				if (nc < dispcost[2 * u])
					dispcost[2 * u] = nc;
			}
			if (times && equals && u * u < 1000 && u != 0) {
				int nc = w + 2;
				if (nc < dist[u * u]) {
					dist[u * u] = nc;
					pq.push({nc, u * u});
				}
				if (nc < dispcost[u * u])
					dispcost[u * u] = nc;
			}
			if (divides && equals && u != 0) {
				int nc = w + 2;
				if (nc < dist[1]) {
					dist[1] = nc;
					pq.push({nc, 1});
				}
				if (nc < dispcost[1])
					dispcost[1] = nc;
			}
			// Try expanding: just use an operator and a number
			for (int v = 1; v < 1000; ++v) {
				if (nct[v] == -1) continue;
				if (plus && u + v < 1000) {
					int nc = w + 1 + nct[v];
					if (nc < dist[u + v]) {
						dist[u + v] = nc;
						pq.push({nc, u + v});
					}
					if (nc + 1 < dispcost[u + v])
						dispcost[u + v] = nc + 1;
				}
				if (minus && u - v > 0) {
					int nc = w + 1 + nct[v];
					if (nc < dist[u - v]) {
						dist[u - v] = nc;
						pq.push({nc, u - v});
					}
					if (nc + 1 < dispcost[u - v])
						dispcost[u - v] = nc + 1;
				}
				if (times && u * v < 1000) {
					int nc = w + 1 + nct[v];
					if (nc < dist[u * v]) {
						dist[u * v] = nc;
						pq.push({nc, u * v});
					}
					if (nc + 1 < dispcost[u * v])
						dispcost[u * v] = nc + 1;
				}
				if (divides && u / v > 0) {
					int nc = w + 1 + nct[v];
					if (nc < dist[u / v]) {
						dist[u / v] = nc;
						pq.push({nc, u / v});
					}
					if (nc + 1 < dispcost[u / v])
						dispcost[u / v] = nc + 1;
				}
			}
		}
		
		if (dispcost[N] < 1e8) cout << dispcost[N];
		else cout << "impossible";
		cout << endl;
	}
	
	
	return 0;
}

