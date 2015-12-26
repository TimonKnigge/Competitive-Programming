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
	
	freopen("highcard.in", "r", stdin);
	freopen("highcard.out", "w", stdout);
	
	int N;
	scanf("%d", &N);
	
	vb b(2*N, true);
	for (int i = 0; i < N; ++i) {
		int v;
		scanf("%d", &v);
		b[v - 1] = false;
	}
	
	vi p1, p2;
	for (int i = 0; i < 2 * N; ++i)
		if (b[i])	p1.push_back(i);
		else		p2.push_back(i);
	
	sort(p1.begin(), p1.end());
	sort(p2.begin(), p2.end());
	
	int ans = 0, j = 0;
	for (int i = 0; i < N; ++i) {
		while (j < N && p1[j] < p2[i]) ++j;
		if (j < N && p1[j] > p2[i]) {
			ans++;
			j++;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
