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
	
	int N, B;
	cin >> N >> B;
	
	vi T(N, 0LL), D(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> T[i] >> D[i];
	
	vi E(N, -1LL);
	queue<int> q;
	ll tf = 0LL;
	for (int i = 0; i < N; ++i) {
		
		while (!q.empty() && E[q.front()] <= T[i])
			q.pop();
		
		if (q.size() <= B) {
			tf = E[i] = max(tf, T[i]) + D[i];
			q.push(i);
		}
	}
	
	for (int i = 0; i < N; ++i)
		cout << E[i] << " \n"[i + 1 == N];

	return 0;
}
