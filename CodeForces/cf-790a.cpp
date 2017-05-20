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

string name(int i) {
	++i;
	string s = "";
	bool fst = false;
	while (i > 0) {
		s = s + string(1, char((fst ? 'a' : 'A') + i % 26));
		i /= 26;
		fst = true;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	vb y(n-k+1, false);
	string S;
	for (int i = 0; i < n - k + 1; ++i) {
		cin >> S;
		y[i] = (S[0] == 'Y');
	}
	
	vi ans(n, 0);
	for (int i = 0; i + 1 < k; ++i) ans[i] = i;
	
	int nxt = k - 1;
	for (int i = k - 1; i < n; ++i) {
		if (y[i - k + 1])
			ans[i] = nxt++;
		else	ans[i] = ans[i - k + 1];
	}
	
	for (int i = 0; i < n; ++i)
		cout << name(ans[i]) << " \n"[i + 1 == n];
	
	return 0;
}
