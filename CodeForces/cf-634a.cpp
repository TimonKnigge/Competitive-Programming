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
	vi A, B;
	for (int i = 0, v; i < N; ++i) {
		cin >> v;
		--v;
		if (v >= 0) A.push_back(v);
	}
	for (int i = 0, v; i < N; ++i) {
		cin >> v;
		--v;
		if (v >= 0) B.push_back(v);
	}
	--N;
	
	vi SA(N, 0LL), SB(N, 0LL);
	for (int i = 0; i < N; ++i) {
		SA[A[i]] = A[(i+1)%N];
		SB[B[i]] = B[(i+1)%N];
	}
	
	bool pos = true;
	for (int i = 0; i < N; ++i)
		pos = pos && SA[i] == SB[i];
	
	cout << (pos ? "YES" : "NO") << endl;

	return 0;
}
