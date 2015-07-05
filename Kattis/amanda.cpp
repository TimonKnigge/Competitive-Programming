#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const int ZERO_LOUNGES = 0, ONE_LOUNGE = 1, TWO_LOUNGES = 2;
const int NO_LOUNGE = 0, DEF_LOUNGE = 1, INDETERMINATE = -1;

bool consistent(int l1, int l2, int est) {
	switch (est) {
	case ZERO_LOUNGES:
		return (l1 == NO_LOUNGE && l2 == NO_LOUNGE);
		break;
	case ONE_LOUNGE:
		return (l1 == NO_LOUNGE && l2 == DEF_LOUNGE)
			|| (l1 == DEF_LOUNGE && l2 == NO_LOUNGE);
		break;
	case TWO_LOUNGES:
		return (l1 == DEF_LOUNGE && l2 == DEF_LOUNGE);
		break;
	default:
		return false;
	}
}

int find_match(int l1, int est) {
	switch (est) {
	case ZERO_LOUNGES:
		return NO_LOUNGE;
		break;
	case TWO_LOUNGES:
		return DEF_LOUNGE;
		break;
	case ONE_LOUNGE:
		return (l1 == NO_LOUNGE ? DEF_LOUNGE : NO_LOUNGE);
		break;
	}
}

void forallIndeterminate(int u, vi& representative, vi& component, vi& status, vector<bool>& vis, vvii& edgelist)
{
	stack<int> st;
	st.push(u);
	while (!st.empty()) {
		int s = st.top(); st.pop();
		if (!vis[s]) continue;
		vis[s] = false;
		status[s] = INDETERMINATE;
		for (ii p : edgelist[s]) {
			int t = p.first;
			if (!vis[t]) continue;
			st.push(t);
		}
	}
}

int tryFill(int u, vi& representative, vi& component, vi& status, vector<bool>& vis, vvii& edgelist)
{
	// Fill trivially
	stack<int> st;
	st.push(u);
	int r = 0;
	while (!st.empty()) {
		int s = st.top(); st.pop();
		if (vis[s]) continue;
		vis[s] = true;
		for (ii p : edgelist[s]) {
			int t = p.first, ltype = p.second;
			if (vis[t]) {
				if (!consistent(status[s], status[t], ltype))
					return -1;
			}
			else{
				if (status[t] == INDETERMINATE) {
					status[t] = find_match(status[s], ltype);
					if (status[t] == DEF_LOUNGE)
						r++;
				}
				if (!consistent(status[s], status[t], ltype))
					return -1;
				st.push(t);
			}
		}
	}
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// Read input
	int n, m, lounges = 0;
	cin >> n >> m;
	vvii edgelist(n); // (target, loungetype)
	vi status(n, INDETERMINATE);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		edgelist[a].push_back(make_pair(b, c));
		edgelist[b].push_back(make_pair(a, c));
		if (c == 0) {
			if (status[a] == DEF_LOUNGE || status[b] == DEF_LOUNGE) {
				cout << "impossible" << endl;
				return 0;
			}
			status[a] = status[b] = NO_LOUNGE;
		}
		if (c == 2){
			if (status[a] == NO_LOUNGE || status[b] == NO_LOUNGE) {
				cout << "impossible" << endl;
				return 0;
				status[a] = status[b] = DEF_LOUNGE;
				lounges += 2;
			}
		}
	}

	// Floodfill, find a representative of each component,
	// (preferably one that is already determined).
	vi component(n, -1); int comp = 0;
	vi representative;
	for (int u = 0; u < n; ++u) {
		if (component[u] != -1) continue;
		queue<int> qu;
		qu.push(u);
		representative.push_back(u);
		while (!qu.empty()) {
			int t = qu.front(); qu.pop();
			if (component[t] != -1) continue;
			component[t] = comp;
			if (status[t] != INDETERMINATE)
				representative[comp] = t;
			for (ii p : edgelist[t]) {
				if (component[p.first] != -1) continue;
				qu.push(p.first);
			}
		}
		comp++;
	}

	// For each component, fill
	vector<bool> vis(n, false);
	for (int c = 0; c < comp; ++c) {
		int u = representative[c];
		if (status[u] != INDETERMINATE) {
			int component_count = tryFill(u, representative, component, status, vis, edgelist);
			if (component_count == -1) {
				cout << "impossible" << endl;
				return 0;
			}
			else lounges += component_count;
		}
		else {
			status[u] = DEF_LOUNGE;
			int m1 = tryFill(u, representative, component, status, vis, edgelist);
			forallIndeterminate(u, representative, component, status, vis, edgelist);
			status[u] = NO_LOUNGE;
			int m2 = tryFill(u, representative, component, status, vis, edgelist);
			if (m1 == -1 && m2 == -1) {
				cout << "impossible" << endl;
				return 0;
			}
			else {
				if (m1 == -1) m1 = m2 + 2;
				if (m2 == -1) m2 = m1 + 2;
				lounges += min(1 + m1, m2);
			}
		}
	}

	cout << lounges << endl;
	return 0;
}