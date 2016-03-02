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

ll gcd(ll a, ll b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M;
	cin >> N >> M;
	
	vvi C(M+1, vi());
	for (int i = 0; i < N; ++i) {
		int v;
		cin >> v;
		if (v > M) continue;
		C[v].push_back(i);
	}
	
	vi dv(M+1, 0LL);
	for (int i = 1; i <= M; ++i) {
		for (int j = i; j <= M; j += i)
			dv[j] += C[i].size();
	}
	
	int best = 1;
	for (int i = 2; i <= M; ++i)
		if (dv[i] > dv[best]) best = i;
	
	vi ind;
	for (int i = 1; i <= M; ++i) {
		if (best % i != 0) continue;
		for (int j : C[i]) ind.push_back(j);
	}
	
	sort(ind.begin(), ind.end());
	cout << best << ' ' << ind.size() << endl;
	for (int i = 0; i < ind.size(); ++i) {
		if (i > 0) cout << ' ';
		cout << ind[i]+1;
	}
	cout << endl;
	
	return 0;
}
