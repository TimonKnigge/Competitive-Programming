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

int N;

ll optimal(
	priority_queue<pair<pair<ll, bool>, ii> > &pq,
	vi &B, vb &F, int rem) {
	if (rem == 0 || pq.size() == 0) return 0LL;
	
	auto tp = pq.top();
	pq.pop();
	if (!F[tp.second.first] || !F[tp.second.second]) {
		ll ret = optimal(pq, B, F, rem);
		pq.push(tp);
		return ret;
	}
	
	int l = tp.second.second, r = tp.second.first, ob;
	
	// Branch on l,r
	F[l] = F[r] = false;
	ll opt = tp.first.first + optimal(pq, B, F, rem - 1);
	bool type = tp.first.second;
	F[l] = F[r] = true;
	
	// branch from l
	F[l] = false;
	if (l % N != 0) {
		ob = l - 1;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[l] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	if (l >= N) {
		ob = l - N;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[l] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	if ((!type && (l + N) < N * N)
		|| (type && (l+1) % N != 0)) {
		ob = (!type) ? l + N : l + 1;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[l] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	F[l] = true;

	// branch from r
	F[r] = false;
	if (r % N != N - 1) {
		ob = r + 1;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[r] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	if (r + N < N * N) {
		ob = r + N;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[r] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	if ((!type && (r - N) >= 0)
		|| (type && r % N != 0)) {
		ob = (!type) ? r - N : r - 1;
		if (F[ob]) {
			F[ob] = false;
			opt = max(opt, B[ob] + B[r] + optimal(pq, B, F, rem-1));
			F[ob] = true;
		}
	}
	F[r] = true;
	
	pq.push(tp);
	
	return opt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int K;
	cin >> N >> K;
	
	vi B(N * N, 0LL);
	vb F(N * N, true);
	priority_queue<pair<pair<ll, bool>, ii> > pq;
	ll sum = 0LL;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c) {
			cin >> B[r + c * N];
			sum += B[r + c * N];
			if (r > 0)
				pq.push({{B[r+c*N] + B[r-1+c*N], false},
					 {r+c*N, r-1+c*N}});
			if (c > 0)
				pq.push({{B[r+c*N] + B[r+c*N-N], true},
					 {r+c*N, r+c*N-N}});
		}
	
	cout << sum - optimal(pq, B, F, K) << endl;
	
	return 0;
}
