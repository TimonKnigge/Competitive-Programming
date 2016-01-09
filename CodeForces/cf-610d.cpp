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

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<pair<ii, int> > H;
	vector<pair<int, ii> > V;
	for (int i = 0; i < N; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (y1 == y2)	H.push_back({{x1, x2}, y1});
		else		V.push_back({x1, {y1, y2}});
	}
	
	sort(H.begin(), H.end());
	sort(V.begin(), V.end());
	
	ll ans = 0LL;
	int j = 0;
	map<int, ii> active;
	for (int i = 0; i < int(V.size()); ++i) {
		// Exit horizontal segments
		// Enter horizontal segments.
		while (j < int(H.size()) && H[j].first <= V[i].first) {

		}
	}
	
	return 0;
}
