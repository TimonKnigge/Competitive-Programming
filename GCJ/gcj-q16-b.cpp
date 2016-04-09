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
		
		string S;
		cin >> S;
		
		int ans = 0, r = S.size() - 1;
		
		while (r >= 0) {
			if (S[r] == '+') {
				--r;
				continue;
			}
			
			if (S[0] == '+') {
				int l = 0;
				while (S[l] == '+') ++l;
				
				++ans;
				for (int i = 0; i < l; ++i)
					S[i] = '-';
			}
			
			for (int i = 0; i <= r / 2; ++i) {
				swap(S[i], S[r - i]);
			}
			for (int i = 0; i <= r; ++i)
				S[i] = (S[i] == '+' ? '-' : '+');
			++ans;
		}
		
		cout << "Case #" << t << ": ";
		cout << ans << '\n';
	}
	
	return 0;
}
