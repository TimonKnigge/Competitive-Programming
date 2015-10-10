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

int mapmapmap(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	else return 10 + (c - 'a');
}

int main() {
	freopen("filter.in", "r", stdin);
	freopen("filter.out", "w", stdout);
	
	int m, f;
	scanf("%d %d", &m, &f);
	vector<ll> a(f, 0);
	for (int i = 0; i < f; ++i) { int x; scanf("%d", &x); a[i] = x; }
	
	int n;
	scanf("%d", &n);
	vector<vector<bool> > filter(n, vector<bool>(m, false));
	
	int bitl = (1 + (m - 1) / 4);
	for (int i = 0; i < n; ++i) {
		char c;
		for (int j = 0; j < bitl; ++j) {
			scanf(" %c", &c);
			int v = mapmapmap(c);
			filter[i][4 * j    ] = bool( v     & 1);
			filter[i][4 * j + 1] = bool((v>>1) & 1);
			filter[i][4 * j + 2] = bool((v>>2) & 1);
			filter[i][4 * j + 3] = bool((v>>3) & 1);
		}
	}
	
	int q;
	scanf("%d", &q);
	vi hash(f, 0);
	vb fileyes(n, false);
	int FILES = 0;
	for (int i = 0; i < q; ++i) {
		int x; ll uk;
		scanf("%d", &x); uk = x;
		
		for (int j = 0; j < f; ++j) hash[j] = (uk * a[j]) % m;
		for (int j = 0; j < n; ++j) {
			if (fileyes[j]) continue;
			bool yes = true;
			for (int k = 0; k < f && yes; ++k) yes = yes && filter[j][hash[k]];
			if (yes) { FILES++; fileyes[j] = true; }
		}
	}
	
	printf("%d", FILES);
	for (int i = 0; i < n; ++i) {
		if (!fileyes[i]) continue;
		printf(" ");
		printf("%d", i);
	}
	printf("\n");
	fflush(stdin);
	
	return 0;
}
