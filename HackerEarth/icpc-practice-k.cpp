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
	
	int N, Q;
	scanf("%d %d", &N, &Q);
	
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	for (int a, b, i = 0; i < Q; ++i)
		scanf("%d %d", &a, &b),
		pq.push({a, b});
	
	int ans = pq.size();
	for (int i = 1; i <= N; ++i) {
		if (pq.size() == 0 || pq.top().first != i) {
			ans = 0;
			break;
		}
		
		int a = pq.top().first, b = pq.top().second, c = 1;
		pq.pop();
		
		while (pq.size() > 0 && pq.top().first == a) {
			int bb = pq.top().second;
			++c;
			pq.pop();
			if (bb > b) pq.push({b + 1, bb});
		}
		
		ans = min(ans, c);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
