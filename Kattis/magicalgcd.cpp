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
using ii = pair<int,int>;
using vi = vector<int>;
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

#define T(i) ((i)&1)
#define O(i) (((i)&1)^1)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		vector<ll> A(N, 0LL);
		for (int i = 0; i < N; ++i)
			cin >> A[i];
		
		pair<ll, int> gcdlm[2][100];
		gcdlm[0][0] = {A[0], 0};
		ll best = A[0];
		
		int L[2] = {1, 0};
		
		for (int i = 1; i < N; ++i) {
			L[T(i)] = 0;
			
			for (int j = 0; j < L[O(i)]; ++j) {
				ll g = gcd(gcdlm[O(i)][j].first, A[i]);
				if (L[T(i)] == 0 || 
					gcdlm[T(i)][L[T(i)]-1].first != g) {
					gcdlm[T(i)][L[T(i)]] = 
						{g, gcdlm[O(i)][j].second};
					++L[T(i)];
				}
			}
			
			if (A[i] != gcdlm[T(i)][L[T(i)]-1].first) {
				gcdlm[T(i)][L[T(i)]] = {A[i], i};
				++L[T(i)];
			}
			
			for (int j = 0; j < L[T(i)]; ++j)
				best = max(best, gcdlm[T(i)][j].first
					* (i+1-gcdlm[T(i)][j].second));
		}
		cout << best << '\n';
	}
	
	return 0;
}
