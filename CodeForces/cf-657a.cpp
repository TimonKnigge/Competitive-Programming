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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, D, H;
	cin >> N >> D >> H;
	
	// 1 <= h <= d <= n - 1
	
	if (D > 2 * H || (H == 1 && D == 1 && N > 2)
		|| (D == 1 && N > 2)) {
		cout << -1 << endl;
		return 0;
	}
	
//	cerr << N << " vertices\n" << D << " diameter\n" << H << " height" << endl;
	
	vii E;
	for (int i = 1; i <= H; ++i)
		E.push_back({i, i + 1});
	if (H < D)
		E.push_back({1, H + 2});
	for (int i = 1; i <= D - H - 1; ++i)
		E.push_back({H + 1 + i, H + 2 + i});
	
	int v = (H == D ? 2 : 1);
	while (E.size() + 1 < N)
		E.push_back({v, E.size() + 2});
	
	for (size_t i = 0; i < E.size(); ++i)
		cout << E[i].first << ' ' << E[i].second << '\n';
	
	return 0;
}
