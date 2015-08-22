#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, ll> il;
typedef pair<ll, int> li;
typedef vector<ll> vl;
typedef vector<il> vil;
typedef vector<vil> vvil;

const ll LLINF = 2e18;

int rd() {
	int n = 0, sign = 1;
	register char c;
	while ((c = getc_unlocked(stdin)) != '\n') {
		switch(c) {
			case '-': sign = -1; break;
			case ' ': goto hell;
			case '\n': goto hell;
			default: n *= 10; n += c - '0'; break;
		}
	}
hell:
	return n * sign;
}

void dijkstra(vvil &e, int s, vl &d, int Q) {
	d.assign(e.size(), LLINF);
	vector<bool> ex(e.size(), false);
	priority_queue<li, vector<li>, greater<li> > pq;
	pq.push({0, s});
	d[s] = 0;

	int ask = rd();

	while (!pq.empty()) {
		ll w = pq.top().first;
		int u = pq.top().second; 
		pq.pop();
		
		ex[u] = true;
		if (u == ask) {
			while (ex[ask]) {
				cout << d[ask] << '\n';
				Q--;
				if (Q == 0) return;
				ask = rd();
			}
		}
		if (d[u] < w) continue;
		for (il vx : e[u]) {
			int v = vx.first;
			ll x = vx.second;
			if (d[u] + x < d[v]) {
				d[v] = d[u] + x;
				pq.push({d[v], v});
			}
		}
	}

	for (; Q > 0; --Q) {
		if (!ex[ask]) cout << "Impossible\n";
		else cout << d[ask] << '\n';
		if (Q > 1) ask = rd();
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int n, m, q, s;
		n = rd();
		m = rd();
		q = rd();
		s = rd();
		if (n == 0) break;
		vvil e(n, vil());
		for (int i = 0; i < m; ++i) {
			int u, v; int w;
			u = rd();
			v = rd();
			w = rd();
			e[u].push_back({v, ll(w)});
		}
	
		vl dist;
		dijkstra(e, s, dist, q);
		cout << '\n';
	}
	cout << flush;

	return 0;
}
