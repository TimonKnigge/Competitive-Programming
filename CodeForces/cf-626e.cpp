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

ld solveodd(vector<ll> &A, vector<ll> &S, int N, vi &out) {
	int l = 0;
	ll sum = 0LL;
	ld opt = -LLINF;
	int lopt = -1, ropt = -1;
	for (int r = 0; r < N; ++r) {
		sum += A[r];
		while (N - (r-l) <= r) {
			sum -= A[l];
			++l;
		}
		
		while (l < r && (ld(S[r-l] + sum) / ld(2 * (r-l) +1)
				< ld(S[r-l-1] + sum - A[l]) / ld(2 * (r-l) - 1))) {
			sum -= A[l];
			++l;
		}
		if (ld(S[r - l] + sum) / ld(2 * (r - l) + 1) - A[r] > opt) {
			lopt = l;
			ropt = r;
			opt = ld(S[r-l] + sum) / ld(2 * (r - l) + 1) - A[r];
		}
	}
	
	for (int i = lopt; i <= ropt; ++i)
		out.push_back(i);
	for (int i = max(ropt + 1, N - (ropt - lopt)); i < N; ++i)
		out.push_back(i);
	
	return opt;
}

ld solveeven(vector<ll> &A, vector<ll> &S, int N, vi &out) {
	int l = 0;
	ll sum = 0LL;
	ld opt = -LLINF;
	int lopt = -1, ropt = -1;
	
	for (int r = 0; r < N - 1; ++r) {
		sum += A[r];
		while (N - (r-l) - 1 <= r) {
			sum -= A[l];
			++l;
		}
		while (l < r && (ld(S[r-l+1] + sum) / ld(2 * (r-l+1)) - 0.5 * A[N - (r-l) -1]
				< ld(S[r-l] + sum - A[l]) / ld(2 * (r-l)) - 0.5 * A[N - (r-l)])) {
			sum -= A[l];
			++l;
		}
		if (ld(S[r - l + 1] + sum) / ld(2 * (r - l + 1)) - 0.5 * (A[r] + A[N - (r-l) - 1]) > opt) {
			lopt = l;
			ropt = r;
			opt = ld(S[r-l+1] + sum) / ld(2 * (r - l + 1)) - 0.5 * (A[r] + A[N - (r-l) - 1]);
		}
	}
	
	for (int i = lopt; i <= ropt; ++i)
		out.push_back(i);
	for (int i = max(ropt + 1, N - (ropt - lopt) - 1); i < N; ++i)
		out.push_back(i);
	
	return opt;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vector<ll> A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	sort(A.begin(), A.end());
	
	vector<ll> S(N + 1, 0LL);
	S[0] = 0LL;
	for (int i = 1; i <= N; ++i)
		S[i] = S[i - 1] + A[N - i];
	
	vi evopt, odopt;
	ld odd  = solveodd (A, S, N, odopt);
	ld even = (N > 1 ? solveeven(A, S, N, evopt) : -LLINF);
	
	if (odd > even) {
		cout << odopt.size() << endl;
		for (size_t i = 0; i < odopt.size(); ++i)
			cout << A[odopt[i]] << " \n"[i + 1 == odopt.size()];
	} else {
		cout << evopt.size() << endl;
		for (size_t i = 0; i < evopt.size(); ++i)
			cout << A[evopt[i]] << " \n"[i + 1 == evopt.size()];
	}
	
	return 0;
}
