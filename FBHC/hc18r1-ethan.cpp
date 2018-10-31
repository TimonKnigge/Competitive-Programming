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

void pre(int u, const vi &A, const vi &B, vi &out) {
	if (u < 0) return;
	out.push_back(u);
	pre(A[u], A, B, out);
	pre(B[u], A, B, out);
}
void post(int u, const vi &A, const vi &B, vi &out) {
	if (u < 0) return;
	post(A[u], A, B, out);
	post(B[u], A, B, out);
	out.push_back(u);
}

void solve(int t) {
	int K, N;
	cin >> N >> K;
	vi A(N), B(N);
	for (int i = 0; i < N; ++i)
		cin >> A[i] >> B[i], --A[i], --B[i];

	vi pr, po;
	pre(0, A, B, pr);
	post(0, A, B, po);

	vi perm(N);
	for (int i = 0; i < N; ++i)
		perm[pr[i]] = po[i];

	vi id(N, -1);
	int next = 0;
	for (int i = 0; i < N; ++i) {
		if (id[i] > 0) continue;
		next = min(next + 1, K);
		int j = i;
		do {
			id[j] = next;
			j = perm[j];
		} while (j != i);
	}

	cout << "Case #" << t << ":";
	if (next < K) {
		cout << " Impossible\n";
	} else {
		for (int i = 0; i < N; ++i)
			cout << ' ' << id[i];
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) solve(t);
	cout << flush;
	
	return 0;
}
