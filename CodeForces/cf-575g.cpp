#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long N, M;
	cin >> N >> M;
	vector<vector<pair<long long, long long> > > e(N, vector<pair<long long, long long> >());
	for (long long i = 0; i < M; ++i) {
		long long a, b, len;
		cin >> a >> b >> len;
		e[a].push_back({b, len});
		e[b].push_back({a, len});
	}
	
	// BFS starting from N - 1: mark all vertices that can 
	// reach N - 1 following only zero edges
	queue<long long> qu;
	vector<bool> zeroreach(N, false);
	vector<long long> zeropar(N, -1), zerodis(N, -1);
	zeroreach[N - 1] = true; zerodis[N - 1] = 0; qu.push(N - 1);
	while (!qu.empty()) {
		long long u = qu.front(); qu.pop();
		for (auto vw : e[u]) {
			if (vw.second != 0 || zeroreach[vw.first])
				continue;
			zeroreach[vw.first] = true;
			zeropar[vw.first] = u;
			zerodis[vw.first] = zerodis[u] + 1;
			qu.push(vw.first);
		}
	}
	
	// BFS starting from zero
	long long ans = -1, ansdist = -1;
	vector<long long> answers;
	vector<bool> expanded(N, false);
	vector<long long> par(N, -1), d(N, -1), pref(N, -1);
	d[0] = 0;
	vector<vector<vector<int> > > q(2, vector<vector<int> > (10, vector<int>()));
	q[0][0].push_back(0);
	int qn = 0;
	while (true) {
		bool any = false;
		for (int l = 0; l < 10; ++l) {
			for (int j = 0; j < q[qn%2][l].size(); ++j) {
				int u = q[qn%2][l][j];
				if (expanded[u]) continue;
				else expanded[u] = true;
				if (ansdist != -1 && ansdist != d[u]) continue;
				any = true;
				if (zeroreach[u]) {
					if (ans == -1) ans = u;
					else answers.push_back(u);
					ansdist = d[u];
				} else
				for (auto vw : e[u]) {
					int v = vw.first, w = vw.second;
					if (d[v]==-1 || (d[v]==d[u]+1
						&& pref[v] > w)) {
						q[(qn+1)%2][w]
						.push_back(v);
						d[v] = d[u] + 1;
						par[v] = u;
						pref[v] = w;
					}
				}
			}
			q[qn%2][l].clear();
		}
		if (!any) break; else qn++;
	}
	if (answers.size() > 0) {
		for (size_t i = 0; i < answers.size(); ++i) {
			long long l = ans, r = answers[i];
			bool eq = true;
			while (l != r) {
				if (pref[l] == pref[r]) {
					l = par[l]; r = par[r];
					continue;
				}
				eq = false;
				break;
			}
			if (eq && zerodis[answers[i]] < zerodis[ans])
				ans = answers[i];
		}
	}
	
	// Reconstruct number
	if (d[ans] == 0) cout << 0 << endl;
	else {
		vector<long long> ansvec;
		long long a = ans;
		while (par[a] != -1) {
			ansvec.push_back(pref[a]);
			a = par[a];
		}
		for (long long i = 0; i < (long long)(ansvec.size()); ++i)
			cout << ansvec[i];
		cout << '\n';
	}
	
	// Reconstruct route
	// ans to N - 1
	vector<long long> zeropath, nonzeropath;
	long long a = ans;
	while (zeropar[a] != -1) {
		zeropath.push_back(zeropar[a]);
		a = zeropar[a];
	}
	a = ans;
	while (a != -1) {
		nonzeropath.push_back(a);
		a = par[a];
	}
	
	cout << (zeropath.size() + nonzeropath.size()) << '\n';
	for (long long i = (long long)(nonzeropath.size()) - 1; i >= 0; --i) {
		cout << nonzeropath[i];
		if (i != 0 || zeropath.size() > 0) cout << ' ';
	}
	for (size_t i = 0; i < zeropath.size(); ++i) {
		cout << zeropath[i];
		if (int(i) != int(zeropath.size()) - 1) cout << " ";
	}
	cout << endl;
	
	return 0;
}
