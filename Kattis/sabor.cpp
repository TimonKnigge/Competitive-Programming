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
	
	set<ii> seen;
	vvi E(N, vi());
	for (int d = 0; d < 5; ++d) {
		int p;
		scanf("%d", &p);
		while (p--) {
			int k, l;
			scanf("%d %d", &k, &l);
			--k; --l;
			if (k > l) swap(k, l);
			//if (seen.find({k, l}) != seen.end()) continue;
			E[k].push_back(l);
			E[l].push_back(k);
			seen.insert({k, l});
		}
	}
	
	vb party(N, false);
	for (int i = 0; i < N; ++i) party[i] = bool(rand()&1);
	
	queue<int> q;
	for (int i = 0; i < N; ++i) {
		int con = 0;
		for (int j : E[i])
			if (party[i] == party[j]) ++con;
		if (con > 2) q.push(i);
	}
	
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		
		int con = 0;
		for (int j : E[i])
			if (party[i] == party[j]) ++con;
		if (con > 2) {
			party[i] = !party[i];
			for (int j : E[i]) {
				con = 0;
				for (int k : E[j])
					if (party[j] == party[k]) ++con;
				if (con > 2) q.push(j);
			}
		}
	}
	
	for (int i = 0; i < N; ++i)
		cout << (party[i] ? 'A' : 'B');
	cout << endl;
	
	return 0;
}
