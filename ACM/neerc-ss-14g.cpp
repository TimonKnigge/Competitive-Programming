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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	ll m = 0LL;
	vector<ll> a(N, 0LL);
	for (int i = 0; i < N; ++i) {
		int x;
		scanf("%d", &x);
		a[i] = x;
		if (m > a[i]) m = a[i];
	}
	
	ll sum = 0LL;
	stack<int> st; // Positions with a[i] > m
	for (int i = 0; i < K; ++i) {
		sum += a[i];
		if (a[i] > m) st.push(i);
	}
	
	ll ans = 0LL;
	for (int i = K - 1; i < N; ++i) {
		while (sum >= 0) {
			int j = st.top();
			ll maxpos = a[j] - m;
			ll needed = sum + 1;
			ll diff = min(maxpos, needed);
			sum -= diff;
			a[j] -= diff;
			if (a[j] == m) st.pop();
			ans += diff;
		}
		if (i < N - 1) {
			sum -= a[i - K + 1];
			sum += a[i + 1];
			if (a[i + 1] > m)
				st.push(i + 1);
		}
	}
	
	cout << ans << endl;
	for (int i = 0; i < N; ++i)
		cout << a[i] << " \n"[i == N - 1];
	
	return 0;
}
