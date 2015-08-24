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
	
	vector<int> pid(N + 1, 0);
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		pid[x] = i + 1;
	}

	FenwickTree<ll> ft(N);
	ll inv = 0LL;
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		x = pid[x];
		inv += ft.query(x, N);
		ft.update(x, 1);
	}

	cout << (inv % 2 == 0 ? "Possible" : "Impossible") << endl;
	
	return 0;
}

