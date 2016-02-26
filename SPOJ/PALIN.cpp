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

void solve() {
	string K;
	cin >> K;
	int N = int(K.size());
	
	// Is the current number a palindrome?
	bool p = true;
	for (int i = 0; i < N / 2; ++i)
		p = p && (K[i] == K[N - 1 - i]);
	
	if (p) {
		bool d = false;
		int i = N - 1;
		while (!d && i >= 0) {
			if (K[i] == '9') {
				K[i] = '0';
				--i;
			} else {
				K[i] = char(int(K[i]) + 1);
				d = true;
			}
		}
		if (!d) {
			K = "1" + K;
			++N;
		}
	}
	
	bool inc = false;
	for (int i = 0; i < N / 2; ++i) {
		if (K[i] < K[N-1-i])
			inc = true;
		else if (K[i] > K[N-1-i])
			inc = false;
		K[N-1-i] = K[i];
	}
	if (inc && (N&1) && K[N/2] != '9') {
		K[N/2]++;
		inc = false;
	}
	if (inc) {
		if (N&1) K[N/2] = '0';
		int i = N / 2 - 1;
		while (i >= 0 && inc) {
			if (K[i] == '9') {
				K[i] = '0';
				K[N-1-i] = '0';
				--i;
			} else {
				K[i]++;
				K[N-1-i]++;
				inc = false;
			}
		}
	}
	if (inc) {
		K[N-1] = '1';
		K = '1' + K;
	}
	cout << K << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) solve();
	
	return 0;
}
