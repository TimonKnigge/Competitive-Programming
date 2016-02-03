#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

bool solve() {
	ll M;
	int N;
	cin >> M >> N;
	
	vii inv;
	for (int i = 0; i < N; ++i) {
		ll A, B;
		cin >> A >> B;
		if (A <= B) {
			inv.push_back({B, A});
			inv.push_back({B+M, A+M});
		} else {
			inv.push_back({B+M, A});
		}
	}
	sort(inv.begin(), inv.end());
	if (N > M) return false;
	
	set<int> av;
	for (int i = 0; i < int(inv.size()); ++i) {
		ll A = inv[i].second, B = inv[i].first;
		auto it = av.lower_bound(A);
		while (*it == A && it != av.end()) { ++it; ++A; }
		if (A > B) return false;
		else av.insert(A);
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) cout << (solve() ? "YES" : "NO") << '\n';
	cout << flush;
	
	return 0;
}
