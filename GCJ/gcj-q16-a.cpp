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
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		
		vb seen(10, false);
		
		ll N, left = 10;
		cin >> N;
		
		ll C = N;
		for (int i = 0; i < 1e5 && C < 1e18; ++i, C += N) {
			
			ll V = C;
			while (V > 0) {
				if (!seen[V % 10]) {
					seen[V%10] = true;
					--left;
				}
				V /= 10;
			}
			if (left == 0) break;
		}
		
		cout <<"Case #" << t << ": ";
		if (left == 0) cout << C;
		else cout << "INSOMNIA";
		cout << '\n';
	}
	
	return 0;
}
