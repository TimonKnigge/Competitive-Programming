#include <iostream> 
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
	int n, m;
	scanf("%d %d", &n, &m);
	
	vvi iv(n - 1, vi());
	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		a--; b--;
		if (a < b)
			iv[a].push_back(b);
	}
	
	int assign = -1;
	
	for (int i = 0; i < n - 1; ++i) {
		if (iv[i].size() > 0) {
			sort(iv[i].begin(), iv[i].end());
			int l = 0;
			if (assign <= i) {
				assign = iv[i][0];
//				l++;
			}
			// Xor the next value with the rest
			if (l < iv[i].size() && iv[i][l] < n - 1)
			for (int j = l + 1; j < iv[i].size(); ++j) {
				if (iv[i][j] > iv[i][l])
					iv[iv[i][l]].push_back(iv[i][j]);
				l++;
			}
		}
		if (assign > i) cout << '1'; else cout << '0';
	}
	cout << endl;
	
	return 0;
}
