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

bool isp(const string &S, size_t l, size_t r) {
	bool y = true;
	for (size_t i = l; i < l + (r-l)/2; ++i)
		y = y && S[i] == S[r-i-1];
	return y;
}

void solve() {
	string S;
	cin >> S;

	bool sm = true;
	for (size_t i = 0; i < S.length()/2; ++i)
		sm = sm && S[i] == S[0] && S[S.length()-i-1] == S[0];

	if (sm) {
		cout << "Impossible" << endl;
		return;
	}

	if (S.length() % 2 == 1) {
		cout << 2 << endl;
	} else {
		string SS = S+S;
		size_t L = S.length()/2;
		for (size_t i = 0; i < L; ++i) {
			if (std::equal(
				SS.begin()+SS.length()-i-L-1,
				SS.begin()+SS.length()-i-1-1 + 1,
				SS.begin()+i+L+1,
				SS.begin()+i+L+L + 1)) {
				if (!std::equal(
					SS.begin()+i+L+1,
					SS.begin()+i+L+L + 1,
					SS.begin()+L,
					SS.begin()+L+L)) {
						cout << 1 << endl;
						return;
				}
			}
		}
		cout << 2 << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(12);
	
	solve();
	
	return 0;
}
