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
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void res(bool r, vi &v) {
	if (r)
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] + 1 << " \n"[i + 1 == v.size()];
	else cout << -1 << endl;
}

void solve() {
	int N, K;
	cin >> N >> K;
	
	vi v(N, 0);
	for (int i = 0; i < N; ++i) v[i] = i;
	
	if (K == 0 || N % (2 * K) != 0) {
		res(K == 0, v);
		return;
	}
	
	for (int i = 0; i < N; i += 2 * K)
		for (int j = i; j < i + K; ++j)
			swap(v[j], v[j + K]);
	res(true, v);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
