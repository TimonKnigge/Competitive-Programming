#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	vector<long long> seq(n, 0);
	for (int i = 0; i < n; ++i) cin >> seq[i];
	vector<long long> ev_prefix(n, 0), od_prefix(n, 0);
	for (int i = n - 1; i >= 0; --i) {
		long long ai = seq[i];
		ev_prefix[i] = (i + 1 < n ? ev_prefix[i + 1] : 0);
		od_prefix[i] = (i + 1 < n ? od_prefix[i + 1] : 0);
		if (i % 2 == 0)
			ev_prefix[i] += ai;
		else
			od_prefix[i] += ai;
	}

	for (int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		l--; r--;
		long long ans = ev_prefix[l] - od_prefix[l] - (r + 1 < n ? ev_prefix[r + 1] : 0) + (r + 1 < n ? od_prefix[r + 1] : 0);
		if (l % 2 == 1) ans *= -1;
		cout << ans << '\n';
	}
	cout << flush;
	
	return 0;
}
