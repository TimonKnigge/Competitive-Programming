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

inline void f(ll &l, ll r) { if (l < r) l = r; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, n[3];
	string S;
	cin >> N >> S >> n[0] >> n[1] >> n[2];

	vi pos, neg;
	bool plus = true;
	int count = 1;
	S = S + "+";
	for (size_t i = 1; i < S.length(); i += 2) {
		switch (S[i]) {
			case '+': {
				(plus ? pos : neg).push_back(count);
				count = 1, plus = true;
				break;
			}
			case '-': {
				(plus ? pos : neg).push_back(count);
				count = 1, plus = false;
				break;
			}
			case '*': {
				++count;
				break;
			}
		}
	}

	ll ans = 0LL;
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());

	cerr << "pos:"; for (ll p : pos) cerr << ' ' << p; cerr << endl;
	cerr << "neg:"; for (ll p : neg) cerr << ' ' << p; cerr << endl;

	// Use 0s to cancel out as many negatives as possible.
	int sink = 0;
	while (!neg.empty() && n[0] > 0) {
		sink += (int)neg.back() - 1;
		neg.pop_back();
		n[0]--;
	}

	// Still 0s left? Sink as many as possible.
	if (n[0] > 0) {
		int rm0 = min(n[0], sink);
		n[0] -= rm0, sink -= rm0;
	}

	// If there are no more 0s we need to allocate only 2s and 1s.
	if (n[0] == 0) {
		// Allocate as many 2s together as possible.
		while (!pos.empty()) {
			int pw2 = min((int)pos.back(), n[2]);
			ans += (1LL << pw2);
			pos.pop_back();
			n[2] -= pw2;
		}
		// Now we still need to allocate negatives. Spread 2s evenly. Sink fst.
		int rm2 = min(sink, n[2]);
		sink -= rm2;
		n[2] -= rm2;
		if (!neg.empty()) {
			vi each(neg.size(), 1LL);
			for (int i = 0; n[2] > 0; i = (i + 1) % each.size())
				if (neg[i] > 0)
					each[i] <<= 1, --neg[i], --n[2];
			ans -= accumulate(each.begin(), each.end(), 0LL);
		}
	} else if (n[2] == 0) {
		// No more 2s, so we just greedily group as many 1s together as pos.
		for (size_t i = 0; i < pos.size(); ++i) {
			int am0 = min((int)pos[i], n[1]);
			n[1] -= am0;
			if (am0 == pos[i]) ++ans;
		}
	} else if (!pos.empty() && n[1] + n[2] >= pos[0]) {
		ll best = 0LL, extra = 0LL;
		while (!pos.empty() && n[1] + n[2] >= pos[0]) {
			ll add = 0LL;
			int i = 0;
			int sum = 0, n0 = n[0], n1 = n[1], n2 = n[2];
			while (n1 + n2 >= sum + pos[i]) sum += pos[i++];
			for (int j = i - 1; j >= 0; --j)
				add += (1LL<<min(n2, (int)pos[j])),
				n2 -= min(n2, (int)pos[j]);

			best = max(best, add + extra);

			int bj = -1;
			n2 = n[2];
			for (int j = 0; j < (int)pos.size(); ++j)
				if (n1 + n2 >= pos[j] && (bj < 0
						|| min(n2, (int)pos[j]) > min(n2, (int)pos[bj])
						|| (min(n2, (int)pos[j]) == min(n2, (int)pos[bj])
							&& pos[j] < pos[bj])))
					bj = j;
			if (bj < 0) break;
			int ts = min(n2, (int)pos[bj]);
			extra += (1LL<<ts);
			n[2] = n2 = (n2 - ts);
			n[1] = n1 = (n1 - (pos[bj]-ts));
			pos.erase(pos.begin()+bj);
			best = max(best, extra);
		}
		ans += best;
	}

	cout << ans << endl;

	return 0;
}
