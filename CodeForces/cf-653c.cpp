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
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	
	set<int> inc;
	for (int i = 0; i + 1 < N; i += 2) {
		if (A[i] >= A[i + 1]) {
			inc.insert(i);
			inc.insert(i+1);
		}
	}
	for (int i = 1; i + 1 < N; i += 2) {
		if (A[i] <= A[i + 1]) {
			inc.insert(i);
			inc.insert(i+1);
		}
	}
	
	if (inc.size() > 6) {
		cout << 0 << endl;
		return 0;
	}
	
	set<ii> swaps;
	for (ll j : inc) {
		for (ll i = 0; i < N; ++i) {
			if (i == j) continue;
			
			// swap i, j
			swap(A[i], A[j]);
			
			bool valid = true;
			if (i&1) {
				if (i > 0) valid = valid && (A[i-1] < A[i]);
				if (i+1<N) valid = valid && (A[i+1] < A[i]);
			} else {
				if (i > 0) valid = valid && (A[i-1] > A[i]);
				if (i+1<N) valid = valid && (A[i+1] > A[i]);
			}
			for (ll k : inc) {
				if (k&1) {
					if (k > 0) valid = valid && (A[k-1] < A[k]);
					if (k+1<N) valid = valid && (A[k+1] < A[k]);
				} else {
					if (k > 0) valid = valid && (A[k-1] > A[k]);
					if (k+1<N) valid = valid && (A[k+1] > A[k]);
				}
			}
			swap(A[i], A[j]);
			if (valid) swaps.insert({min(i, j), max(i, j)});
		}
	}
	
	cout << swaps.size() << endl;
	
	return 0;
}
