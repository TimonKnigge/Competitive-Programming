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

template<class T>
int longest_increasing_subsequence(vector<T> &a) {
	set<T> st;
	typename set<T>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
	}
	return st.size();
}

int solver(int N, vi &p) {
	int ans = INF;
	for (int i = 0; i < N; ++i) {
		ans = min(ans, N - longest_increasing_subsequence(p));
		for (int j = 1; j < N; ++j)
			swap(p[j], p[j - 1]);
	}
	return ans;
}

void solve(int N) {
	vvi nb(N, vi());
	for (int i = 0; i < N; ++i) {
		int l, r;
		cin >> l >> r;
		--l; --r;
		nb[i].push_back(l);
		nb[i].push_back(r);
	}
	vb vis(N, false);
	int id = 0;
	vi p;
	while (id >= 0) {
		vis[id] = true;
		p.push_back(id);
		int n = -1;
		for (int v : nb[id]) {
			if (!vis[v]) n = v;
		}
		id = n;
	}
	
	if (p.size() < N) {
		cout << "Not solvable.\n";
		return;
	}
	
	cout << "Knot solvable.\n";
	int ans = solver(N, p);
	reverse(p.begin(), p.end());
	ans = min(ans, solver(N, p));
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	while (cin >> N) if (N == 0) break; else solve(N);
	
	return 0;
}
