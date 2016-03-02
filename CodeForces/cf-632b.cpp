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
	vi P(N, 0LL);
	ll S = 0LL;
	for (int i = 0; i < N; ++i)
		cin >> P[i], S += P[i];
		
	string s;
	cin >> s;
	
	ll B = 0LL;
	for (int i = 0; i < N; ++i)
		if (s[i] == 'B') B += P[i];
	
	ll best = max(B, S - B);
	for (int i = 0; i < N; ++i) {
		if (s[i] == 'A') B += P[i];
		else B -= P[i];
		best = max(max(B, S-B), best);
	}
	
	cout << best << endl;
	
	return 0;
}
