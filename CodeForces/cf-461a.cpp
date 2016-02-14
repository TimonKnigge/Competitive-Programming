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
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	sort(A.begin(), A.end());
	
	vi S(N, 0LL);
	S[N - 1] = A[N - 1];
	for (int i = N - 2; i >= 0; --i)
		S[i] = S[i + 1] + A[i];
	
	ll ans = S[0];
	for (int i = 0; i < N; ++i) {
		ans += S[i];
	}
	ans -= S[N - 1];
	
	cout << ans << endl;
	
	return 0;
}
