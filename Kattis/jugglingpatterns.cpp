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

void f(string &P) {
	ll X = 0LL;
	for (size_t i = 0; i < P.size(); ++i)
		X += (P[i] - '0');
	
	if (X % P.length() != 0) {
		cout << P << ": " << "invalid # of balls" << endl;
		return;
	}
	
	priority_queue<ll, vector<ll>, greater<ll>> pq;
	ll balls = X / P.length();
	
	bool valid = true;
	for (ll i = 0; valid && i < X / P.length()
					+ P.length() * P.length(); ++i) {
		if (P[i % P.length()] == '0') {
			valid = valid && (pq.empty() || i < pq.top());
		} else {
			if (pq.empty() || i < pq.top() && balls > 0) {
				pq.push(i);
				--balls;
			}
			valid = valid && i == pq.top();
			pq.pop();
			valid = valid && (pq.empty() || i < pq.top());
			pq.push(i + P[i % P.length()] - '0');
		}
	}
	if (valid)
		cout << P << ": valid with " << X/P.length() << " balls" << endl;
	else	cout << P << ": invalid pattern" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string P;
	while (cin >> P) f(P);
	
	return 0;
}
