#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream fin("sprinklers.in");
	ofstream fout("sprinklers.out");

	int N;
	fin >> N;
	vii P(N);
	for (ii &p : P) fin >> p.first >> p.second;
	sort(P.begin(), P.end());

	vb ru(N, false), fd(N, false);
	int lst = INF;
	for (int i = 0; i < N; ++i) {
		if (P[i].second >= lst) ru[i] = true;
		else lst = P[i].second;
	}
	lst = -INF;
	for (int i = N-1; i >= 0; --i) {
		if (P[i].second <= lst) fd[i] = true;
		else lst = P[i].second;
	}

	vii U, L;
	for (int i = 0; i < N; ++i) {
		if (ru[i] != fd[i]) continue;
		if (ru[i])
			L.push_back(P[i]);
		else
			U.push_back(P[i]);
	}

	if (U.empty() || L.empty()) {
		fout << 0 << endl;
		return 0;
	}

	constexpr ll M = 1e9+7;
	int l = 0, r = 0;
	while (
	
	return 0;
}
