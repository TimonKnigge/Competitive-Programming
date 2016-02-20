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
	
	int N;
	cin >> N;
	vector<string> S(N, "");
	for (int i = 0; i < N; ++i)
		cin >> S[i];
	
	ll ans = 0LL;
	vi row(N, 0LL), col(N, 0LL);
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c)
			if (S[r][c] == 'C') {
				ans += row[r] + col[c];
				row[r]++;
				col[c]++;
			}
	
	cout << ans << endl;
	
	return 0;
}
