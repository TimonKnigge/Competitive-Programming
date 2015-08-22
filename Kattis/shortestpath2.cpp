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

struct pr {
	int v, t0, P, d;
};

void readn(register int *n) {
	int sign = 1;
	register char c;
	*n = 0;
	while ((c = getc_unlocked(stdin)) != '\n') {
		switch(c) {
			case '-': sign = -1; break;
			case ' ': goto hell;
			case '\n': goto hell;
			default: *n *= 10; *n += c - '0'; break;
		}
	}
hell:
	*n *= sign;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (true) {
		int n, m, q, s;
		readn(&n);
		readn(&m);
		readn(&q);
		readn(&s);
		if (n == 0) break;
		
		vector<vector<pr> > e(n, vector<pr>());
		for (int i = 0; i < m; ++i) {
			int u, v, t0, P, d;
			readn(&u);
			readn(&v);
			readn(&t0);
			readn(&P);
			readn(&d);
			e[u].push_back({v, t0, P, d});
		}

		vl dist(n, LLINF);
		dist[s] = 0;
		priority_queue<li, vector<li>, greater<li> > pq;
		pq.push({0, s});
		while (!pq.empty()) {
			ll w = pq.top().first, u = pq.top().second;
			pq.pop();

			if (w == dist[u]) {
				for (pr ed : e[u]) {
					ll dst = LLINF;
					if (ed.t0 >= w && ed.P == 0)
						dst = ed.t0 + ed.d;
					else if (ed.P > 0) {
						dst = ed.t0 + max(0LL, w - ed.t0) / ed.P * ed.P;
						if (dst < w) dst += ed.P;
						dst += ed.d;
					}
					if (dst < dist[ed.v]) {
						dist[ed.v] = dst;
						pq.push({dst, ed.v});
					}
				}
			}
		}

		for (int i = 0; i < q; ++i) {
			int a;
			readn(&a);
			if (dist[a] == LLINF) cout << "Impossible\n";
			else cout << dist[a] << '\n';
		}
		cout << '\n';
	}
	cout << flush;

	return 0;
}
