#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll n, k;
	cin >> n >> k;
	cout << ((n / k) % 2 == 1 ? "YES" : "NO") << endl;
	
	return 0;
}
