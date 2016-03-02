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
	
	ll N, P;
	cin >> N >> P;
	
	vector<string> S(N, "");
	for (int i = 0; i < N; ++i)
		cin >> S[i];
	
	ll R = 0LL;
	for (int i = N - 1; i >= 0; --i)
		R = 2 * R + (S[i] == "halfplus" ? 1LL : 0LL);
	
	cout << (R * P - __builtin_popcountll(R) * P / 2LL) << endl;
	
	return 0;
}
