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

void recurse(int i, int N, int &J, vb &sol) {
	
	if (J == 0) return;
	if (i < N) {
		sol[i] = true;
		recurse(i+1, N, J, sol);
		sol[i] = false;
		recurse(i+1, N, J, sol);
	} else {
		if (!sol[0] || !sol[N - 1]) return;
		int c = 0, alt = 0;
		for (int j = N - 1, s = 1; j >= 0; --j, s = -s)
			if (sol[i]) {
				++c;
				alt += s;
			}
		if (c % 2 != 0) return;			// 3,5,7,9
		if ((36 + alt) % 3 != 0) return;	// 2,8
		if (c % 3 != 0) return;			// 4, 10
		if ((70 + alt) % 7 != 0) return;	// 6
		
		for (int j = N - 1; j >= 0; --j)
			cout << (sol[j] ? '1' : '0');
		cout << " 3 2 3 2 7 2 3 2 3\n";
		--J;
	}
}

void solve(int N, int J) {
	
	vb sol(N, false);
	recurse(0, N, J, sol);
	
	cerr << J << "!" << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	while (T--) {
		int N, J;
		cin >> N >> J;
		cout << "Case #1: ";
		cout << endl;
		solve(N, J);
	}
	
	return 0;
}
