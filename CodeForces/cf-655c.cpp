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
	
	int N, K;
	cin >> N >> K;
	
	string B;
	cin >> B;
	
	vi inds;
	for (int i = 0; i < N; ++i) {
		if (B[i] == '0')
			inds.push_back(i);
	}
	
	ll ans = INF;
	size_t l = 0, r = K, mid = 0;
	while (r < inds.size()) {
		// see if mid+1 is a better place
		while (mid + 1 <= r && 
			max(inds[mid] - inds[l], inds[r] - inds[mid]) > 
			max(inds[mid+1]-inds[l], inds[r]-inds[mid+1]))
			++mid;
		
		ans = min(ans, max(inds[mid]-inds[l], inds[r]-inds[mid]));
		
		++r;
		++l;
	}
	
	cout << ans << endl;
	
	return 0;
}
