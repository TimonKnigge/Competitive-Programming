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

	ifstream fin("greedy.in");
	ofstream fout("greedy.out");
	
	int n;
	fin >> n;
	vi c(n);
	for (int i = 0; i < n; ++i) {
		fin >> c[i];
		c[i] = n - 1 - c[i];
	}

	set<int> free;
	for (int i = 0; i < n; ++i) free.insert(i);
	for (int i = 0; i < n; ++i) {
		auto it = free.upper_bound(c[i]);
		--it;
		if ((*it) == 0) {
			fout << n - 1 - i << endl;
			break;
		} else free.erase(it);
	}

	return 0;
}
