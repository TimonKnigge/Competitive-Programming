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
	
	int n;
	scanf("%d", &n);
	vi p(n, -1);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i]);
		p[i]--;
	}
	
	vvi cyc_of_len(n + 1, vi());
	vb vis(n, false);
	for (int i = 0; i < n; ++i) {
		if (vis[i]) continue;
		int l = 1, j = i;
		while (p[j] != i) {
			vis[j] = true;
			j = p[j];
			vis[j] = true;
			l++;
		}
		cyc_of_len[l].push_back(i);
	}
	
	vi np(n, -1);
	
	bool pos = true;
	// Odd cycles
	for (int L = 1; L <= n; L += 2) {
		for (int i : cyc_of_len[L]) {
			vi cyc;
			int j = i;
			cyc.push_back(i);
			while (p[j] != i) {
				cyc.push_back(p[j]);
				j = p[j];
			}
			vi ncyc(L, 0);
			for (j = 0; j < L; ++j)
				ncyc[(2 * j) % L] = cyc[j];
			for (j = 0; j < L; ++j)
				np[ncyc[j]] = ncyc[(j + 1) % L];
		}
	}
	for (int L = 2; L <= n; L += 2) {
		if (cyc_of_len[L].size() % 2 == 1) {
			pos = false;
			break;
		}
		for (int s = 0; s < cyc_of_len[L].size(); s += 2) {
			vi cyc1, cyc2;
			int i1 = cyc_of_len[L][s];
			int i2 = cyc_of_len[L][s + 1];
			int j1 = i1, j2 = i2;
			cyc1.push_back(i1);
			cyc2.push_back(i2);
			while (p[j1] != i1) {
				cyc1.push_back(p[j1]);
				j1 = p[j1];
			}
			while (p[j2] != i2) {
				cyc2.push_back(p[j2]);
				j2 = p[j2];
			}
			vi ncyc(L + L, 0);
			for (int j = 0; j < L; ++j) {
				ncyc[2 * j] = cyc1[j];
				ncyc[2 * j + 1] = cyc2[j];
			}
			for (int j = 0; j < L + L; ++j)
				np[ncyc[j]] = ncyc[(j + 1) % (L + L)];
		}
	}
	
	if (!pos) cout << -1 << endl;
	else {
		for (int i = 0; i < n; ++i)
			cout << (1 + np[i]) << " \n"[i == n - 1];
	}
	
	return 0;
}
