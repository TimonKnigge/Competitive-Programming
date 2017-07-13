#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using iiii = pair<pair<int, int>, pair<int, int>>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;

	// time 0 unav -1
	// time 1 av -1
	// time 2 test1, test2
	// time 3 av1 av2
	// time 4 unav1 unav2
	priority_queue<iiii, vector<iiii>, greater<iiii>> pq;
	pq.push({{0, 1}, {0, -1}});
	pq.push({{2, 0}, {0, -1}});

	vector<unordered_map<ll, int>> adj(n);
	bool pos = false;
	while (m--) {
		int a, b, l, r; cin >> a >> b >> l >> r; --a; --b;
		pq.push({{l, 3}, {a, b}});
		pq.push({{r, 4}, {a, b}});
		if (l == 0 && (a == 0 || b == 0)) pos = true;
	}
	if (pos == false) {
		cout << -1 << endl;
		return 0;
	}

	vector<vi> r(2, vi(n, false));
	while (!pq.empty()) {
		int time = pq.top().first.first,
			type = pq.top().first.second,
			a1 = pq.top().second.first,
			a2 = pq.top().second.second;
		pq.pop();
		
		if (type == 0) {
			r[time&1][a1] = false;
			for (auto it : adj[a1])
				pq.push({{time+1, 2}, {it.first, a1}});
		}
		if (type == 1 && !r[time&1][a1]) {
			r[time&1][a1] = true;
			for (auto it : adj[a1]) {
				pq.push({{time+1, 1}, {it.first, -1}});
			}
			if (a1 == n - 1) {
				cout << time << endl;
				return 0;
			}
		}
		if (type == 2) {
			if (r[time&1][a1] && adj[a1].find(a2) != adj[a1].end())
				pq.push({{time+1, 1}, {a2, -1}});
		}
		if (type == 3) {
			adj[a1][a2]++;
			adj[a2][a1]++;
			pq.push({{time  , 2}, {a1, a2}});
			pq.push({{time+1, 2}, {a1, a2}});
			pq.push({{time  , 2}, {a2, a1}});
			pq.push({{time+1, 2}, {a2, a1}});
		}
		if (type == 4) {
			{
				auto it = adj[a1].find(a2);
				it->second--;
				if (it->second == 0) adj[a1].erase(it);
			}
			{
				auto it = adj[a2].find(a1);
				it->second--;
				if (it->second == 0) adj[a2].erase(it);
			}
			if (adj[a1].size() == 0) {
				if (r[time&1][a1])
					pq.push({{time+2, 0}, {a1, -1}});
				if (r[(time+1)&1][a1])
					pq.push({{time+1, 0}, {a1, -1}});
			}
			if (adj[a2].size() == 0) {
				if (r[time&1][a2])
					pq.push({{time+2, 0}, {a2, -1}});
				if (r[(time+1)&1][a2])
					pq.push({{time+1, 0}, {a2, -1}});
			}
		}
	}

	cout << -1 << endl;
	
	return 0;
}
