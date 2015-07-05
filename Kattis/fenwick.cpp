#include <iostream>
#include <vector>
#include <algorithm>

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
		while (r > 0) s += tree[r], r -= (r & (-r));
		return s;
	}
	void update(int i, T v) {
		while (i <= n) tree[i] += v, i += (i & (-i));
	}
};

int main() {
	ios::sync_with_stdio(false);

	int N, Q;
	cin >> N >> Q;
	
	FenwickTree<ll> ft(N);
	for (int i = 0; i < Q; ++i) {
		char c; cin >> c;
		if (c == '+') {
			int p; ll v;
			cin >> p >> v;
			ft.update(p + 1, v);
		}
		else {
			int p;
			cin >> p;
			if (p == 0)
				cout << "0\n";
			else
				cout << ft.query(p) << '\n';
		}
	}

	return 0;
}