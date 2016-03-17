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
	
	int N;
	scanf("%d", &N);
	
	vi A(N, 0LL), B(N, 0LL);
	for (int i = 0; i < N; ++i) {
		int v;
		scanf("%d", &v);
		A[i] = ll(v);
		B[i] = A[i] + (i > 0 ? B[i-1] : 0LL);
	}
	
	ll mx = 0LL;
	for (int i = 0; i < N; ++i)
		mx += ll(i + 1) * A[i];
	
	vii lns;
	vector<ld> start(1, -std::numeric_limits<ld>::infinity());
	lns.push_back({0, 0});
	for (int i = 0; i < N; ++i) {
		while (lns.size() > 1 && start.back() >= 
			ld( - B[i] - lns.back().second) / ld(lns.back().first - i - 1)) {
			lns.pop_back();
			start.pop_back();
		}
	//	cerr << (i+1) << "x - " << B[i] << " = " << lns.back().first << "x + " << lns.back().second << endl;
		start.push_back(ld( - B[i] - lns.back().second) / ld(lns.back().first - i - 1));

		lns.push_back({i+1, -B[i]});
	}
	
//	for (int i = 0; i < lns.size(); ++i) printf("%.7lf\n", double(start[i]));

	ll bestchange = 0LL;
	int D = 5;
	for (int i = 0; i < N; ++i) {
		ll change = B[i] - A[i] * ll(i+1);
		
		int l = 0, r = int(lns.size()) - 1;
		while (l < r) {
			int m = (l+r+1) / 2;
			if (start[m] > A[i])
				r = m - 1;
			else	l = m;
		}
		for (int j = max(0, l-D); j < min(int(lns.size()), l+D+1); ++j){
			if (bestchange < change + A[i] * lns[j].first + lns[j].second) {
				bestchange = change + A[i] * lns[j].first + lns[j].second;
			}
		}
	}
	
	cout << (mx + bestchange) << endl;
	
	return 0;
}
