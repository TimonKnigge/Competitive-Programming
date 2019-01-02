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
using vd = vector<ld>;

template<class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
// .find_by_order(int r) and .order_of_key(TIn v)

constexpr int INF = 2000000010;
constexpr ll LLINF = 9000000000000000010LL;
constexpr ld PI = acos(-1);

constexpr ll M = 1e18l;

void add(vi &V, int a, ll b) {
	if ((int)V.size() <= a)
		V.resize(a+1);
	V[a] = (V[a] + b) % M;
}

void solve() {
	int N;
	cin >> N;
	--N;

	vi x(N+1, 0);
	x[1] = 1;
	for (int k = 2; k <= N; ++k)
		x[k] = ((1+x[k-1])^(1+x[k-2]));

	vi A(1, 1), B(3, 1);
	for (int k = 2; k <= N; ++k) {
		vi C;
		add(C, 1+x[k-1], 1LL);
		add(C, 1+x[k-2], 1LL);
		for (int i = 0; i < (int)A.size(); ++i)
			if (A[i])
				add(C, (1+i)^(1+x[k-1]), A[i]);
		for (int i = 0; i < (int)B.size(); ++i)
			if (B[i])
				add(C, (1+i)^(1+x[k-2]), B[i]);
		swap(A, B);
		swap(B, C);
	}

	cout << B[0] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
