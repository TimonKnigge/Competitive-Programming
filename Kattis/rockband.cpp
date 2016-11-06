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
	
	int M, S;
	cin >> M >> S;
	vi L(S, 0LL), MX(S, 0LL);
	for (int i = 0; i < S; ++i) cin >> L[i], --L[i], MX[L[i]] = i;
	for (int i = 1; i < M; ++i)
		for (int j = 0, v; j < S; ++j) {
			cin >> v;
			if (MX[v - 1] < j) MX[v - 1] = j;
		}

	int i = -1, l = 0;
	while (i < l) if (l < MX[L[++i]]) l = MX[L[i]];
	
	++l;
	cout << l << endl;
	sort(L.begin(), L.begin() + l);
	for (int i = 0; i < l; ++i)
		cout << L[i]+1 << " \n"[i + 1 == l];
	
	return 0;
}
