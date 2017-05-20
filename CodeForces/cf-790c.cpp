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

int N, V = 0, K = 0, O = 0;
string S;
vi Vs, Ks, Os;	
vi perm, indof;

map<ll, ll> cache;
ll dfs(char p, int Vi, int Ki, int Oi) {
	if (Vi == V && Ki == K && Oi == O)
		return 0LL;
	ll id = (p - 'A') + 100LL * (Vi + 100LL * (Ki + 100LL * Oi));
	auto it = cache.find(id);
	if (it != cache.end()) return it->second;
	
	int nxt = Vi + Ki + Oi;
	ll best = LLINF;

	// Eerst een V of een O, kan altijd.
	if (Vi < V) {
		int Sind = Vs[Vi];
		int ind = indof[Sind], oind = indof[Sind];
		ll swaps = 0LL;
		while (nxt < ind) {
			swap(perm[ind - 1], perm[ind]);
			indof[perm[ind - 1]] = ind - 1;
			indof[perm[ind]] = ind;
			++swaps;
			--ind;
		}
		best = min(best, swaps + dfs(S[Sind], Vi+1, Ki, Oi));
		while (ind < oind) {
			swap(perm[ind], perm[ind + 1]);
			indof[perm[ind]] = ind;
			indof[perm[ind + 1]] = ind + 1;
			++ind;
		}
	}
	if (Oi < O) {
		int Oind = Os[Oi];
		int ind = indof[Oind], oind = indof[Oind];
		ll swaps = 0LL;
		while (nxt < ind) {
			swap(perm[ind - 1], perm[ind]);
			indof[perm[ind - 1]] = ind - 1;
			indof[perm[ind]] = ind;
			++swaps;
			--ind;
		}
		best = min(best, swaps + dfs(S[Oind], Vi, Ki, Oi+1));
		while (ind < oind) {
			swap(perm[ind], perm[ind + 1]);
			indof[perm[ind]] = ind;
			indof[perm[ind + 1]] = ind + 1;
			++ind;
		}
	}
	// K kan alleen als laatste geen V was.
	if (Ki < K && p != 'V') {
		int Kind = Ks[Ki];
		int ind = indof[Kind], oind = indof[Kind];
		ll swaps = 0LL;
		while (nxt < ind) {
			swap(perm[ind - 1], perm[ind]);
			indof[perm[ind - 1]] = ind - 1;
			indof[perm[ind]] = ind;
			++swaps;
			--ind;
		}
		best = min(best, swaps + dfs(S[Kind], Vi, Ki+1, Oi));
		while (ind < oind) {
			swap(perm[ind], perm[ind + 1]);
			indof[perm[ind]] = ind;
			indof[perm[ind + 1]] = ind + 1;
			++ind;
		}
	}
	cache.insert({id, best});
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> ws >> S;
	
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'V') {
			++V;
			Vs.push_back(i);
		} else if (S[i] == 'K') {
			++K;
			Ks.push_back(i);
		} else {
			++O;
			Os.push_back(i);
		}
	}
	
	perm.assign(N, 0LL);
	indof.assign(N, 0LL);
	iota(perm.begin(), perm.end(), 0LL);
	iota(indof.begin(), indof.end(), 0LL);
	
	cout << dfs('-', 0LL, 0LL, 0LL) << endl;
	
	return 0;
}
