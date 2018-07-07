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
	
	ifstream fin("lifeguards.in");
	ofstream fout("lifeguards.out");

	int N, K;
	fin >> N >> K;
	vii P(N);
	for (ii &p : P) fin >> p.first >> p.second;
	sort(P.begin(), P.end());

	{
		vii P2;
		int fst = -1;
		for (ii p : P) {
			if (p.second > fst) {
				P2.push_back(p);
				fst = p.second;
			} else --K;
		}
		if (K < 0) K = 0;
		swap(P, P2);
	}
	N = (int)P.size();

	++N;
	P.push_back({INF, INF});

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		ans += P[i].second - P[i].first;
		if (i > 0)
			ans -= max(0LL, P[i-1].second - P[i].first);
	}
	cerr << "Initieel bedekken we " << ans << endl;
	if (K == 0) {
		fout << ans << endl;
		return 0;
	}

	vvi dp(K+1, vi(N, INF));
	vi best(K+1, INF);
	for (int i = 0; i < N && i <= K; ++i) {
		dp[i][i] = P[i].first - P[0].first;
	}

	for (int i = 1, j = 0; i < N; ++i) {
		int pre = max(P[i].first-P[i-1].second, 0LL);
		while (j < i && P[j].second < P[i].first) {
			int e = i-j-1;
			for (int k = 0; k <= K; ++k)
				best[min(K,e+k)] = min(best[min(K,e+k)],
					dp[k][j]-P[j].second);
			++j;
		}

		if (j < i) {
			int e = i-j-1;
			for (int k = 0; k <= K; ++k) {
				dp[min(K,e+k)][i] = min(
					dp[min(K,e+k)][i],
					dp[k][j]);
			}
		}
		for (int k = 0; k <= K; ++k) {
			if (best[k] == INF) continue;
			dp[k][i] = min(dp[k][i], -pre+best[k]+P[i].first);
		}

		for (int k = K-1; k >= 0; --k) {
			swap(best[k], best[k+1]);
			best[k+1] -= pre;
		}
		best[0] = INF;
	}

	ans -= dp[K][N-1];

	fout << ans << endl;
	
	return 0;
}
