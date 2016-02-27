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
	
	ll a, b, c;
	cin >> a >> b >> c;
	
	vb pos(c + 1, false);
	pos[0] = true;
	for (int i = 0; i <= c - a; ++i)
		pos[i + a] = pos[i + a] || pos[i];
	for (int i = 0; i <= c - b; ++i)
		pos[i + b] = pos[i + b] || pos[i];
	
	cout <<( pos[c] ? "Yes" : "No" )<< endl;
	
	return 0;
}
