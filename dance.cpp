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
#include <cstdio>

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

void extended_euclid(ll a, ll b, ll &x, ll &y, ll &d) {
	ll xx = y = 0;
	ll yy = x = 1;
	while (b) {
		ll q = a / b;
		ll t = b; b = a % b; a = t;
		t = xx; xx = x - q * xx; x = t;
		t = yy; yy = y - q * yy; y = t;
	}
	d = a;
}

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	vi P(N, 0);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &P[i]);
		P[i]--;
	}
	
	vvi cyc_of_len(N + 1, vi());
	vb vis(N, false);
	for (int i = 0; i < N; ++i) {
		if (vis[i]) continue;
		int j = P[i], L = 1;
		vis[i] = true;
		while (j != i) {
			vis[j] = true;
			L++;
			j = P[j];
		}
		cyc_of_len[L].push_back(i);
	}
	
	vi P2(N, -1);
	for (int i : cyc_of_len[1])
		P2[i] = i;
	bool pos = true;
	vis.assign(N, false);
	for (ll L = 2; pos && L <= N; ++L) {
		ll C = cyc_of_len[L].size();
		if (C == 0) continue;
		ll X, Y, M;
		extended_euclid(L, K, X, Y, M);
		// L * X + K * Y = M = ggd(L, K)
		while (Y < 0) Y += L;
		
		if (C % M != 0) {
			pos = false;
			break;
		}
		
		
		// Pick groups of size M, interleaf s^Y
		for (int group = 0; group < C / M; ++ group) {
			vvi p(M, vi());
			// Find M cycles s
			for (int i = 0; i < M; ++i) {
				int j = cyc_of_len[L][group * M + i];
				do {
					p[i].push_back(j);
					j = P[j];
				} while (j != cyc_of_len[L][group*M+i]);
			}
			
			// Interleaf all M s^Y
			if (M == 1) {
				// M = 1, just copy the permutation
				for (int i = 0; i < L; ++i)
					P2[p[0][i]] = p[0][(i + Y) % L];
			} else
			for (int i = 0; i < L; ++i) {
				if (vis[p[0][i]]) continue;
				vi point(M, i);
				
				// Point point[i] to point[i + 1]
				int j = 0;
				while (vis[p[j][point[j]]] == false) {
					vis[p[j][point[j]]] = true;
					P2[p[j][point[j]]] = p[(j+1)%M][point[(j+1)%M]];
					point[j] = (point[j]+Y)%L;
					j = (j + 1) % M;
				}
			}
		}
	}
	
	if (!pos) printf("Impossible\n");
	else for (int i = 0; i < N; ++i) {
		assert(P2[i] != -1);
		printf("%d", P2[i] + 1);
		if (i < N - 1) printf(" ");
		else printf("\n");
	}
	
	return 0;
}
