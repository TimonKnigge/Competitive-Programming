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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	while (t--) {
		int n, s;
		cin >> n >> s;
		string out(n, '$');

		bool conflict = false;
		while (s--) {
			int p;
			string suff;
			cin >> p >> suff;
			p--;
			
			bool asterisk = false;
			for (int i = p; i < n; ++i) {
				if (suff[i - p] == '*') {
					asterisk = true;
					break;
				}
				if (out[i] != '$' && out[i] != suff[i - p])
					conflict = true;
				else out[i] = suff[i - p];
			}
			
			if (asterisk) {
				for (int i = n - 1, j = suff.size() - 1; j >= 0; --j, --i) {
					if (suff[j] == '*') break;
					else if (out[i] != '$' && out[i] != suff[j])
						conflict = true;
					else	out[i] = suff[j];
				}
			}
		}
		
		for (int i = 0; i < n; ++i)
			conflict = conflict || out[i] == '$';
		
		if (conflict) cout << "IMPOSSIBLE\n";
		else cout << out << '\n';
	}
	
	cout << flush;
	
	return 0;
}
