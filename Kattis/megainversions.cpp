#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

template <class T>
class FenwickTree {
private:
	vector<T> tree;
	int n;
public:
	FenwickTree(int n) : n(n) { tree.assign(n + 1, 0); }
	T query(int l, int r) { return query(r) - query(l - 1); }
	T query(int r) {
		T s = 0;
		for (; r > 0; r -= (r & (-r))) s += tree[r];
		return s;
	}
	void update(int i, T v) {
		for (; i <= n; i += (i & (-i))) tree[i] += v;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	FenwickTree<ll> a(N), inv(N);
	ll ans = 0LL;
	for (int i = 0; i < N; ++i) {
		ll ai;
		cin >> ai;
		ai = N - ai + 1;
		
		if (ai > 1)
			ans += inv.query(ai - 1);
		inv.update(ai, (ai > 1 ? a.query(ai - 1) : 0));
		a.update(ai, 1);
	}

	cout << ans << endl;
	
	return 0;
}

