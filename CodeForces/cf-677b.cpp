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
	ll H, K;
	cin >> N >> H >> K;
	
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i) cin >> A[i];
	
	ll secs = 0LL;
	ll inproc = 0LL;
	int nxt = 0;
	
	while (nxt < N || inproc > 0) {
		secs += inproc/K;
		inproc -= K * (inproc/K);
		while (nxt < N && inproc + A[nxt] <= H)
			inproc += A[nxt++];
		if (inproc > 0LL)
			inproc = max(0LL, inproc - K),
			++secs;
	}
	
	cout << secs << endl;
	
	return 0;
}
