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

int MG = 100;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, K;
	cin >> N >> K;
	++N;

	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	
	vi B(N + MG, 0LL);
	for (int i = 0; i + 1 < N + MG; ++i) {
		if (B[i] == 0LL && i >= N) continue;
		if (i < N) B[i] += A[i];
		if (B[i] == 0LL) continue;
		ll sign = (B[i] > 0LL ? 1LL : -1LL);
		B[i] *= sign;
		
		B[i + 1] += sign * (B[i] / 2LL);
		B[i] = sign * (B[i] % 2);
	}
	for (int i = N + MG - 1; i > 0; --i) {
		if ((B[i] == -1LL && B[i - 1] == 1LL) ||
		    (B[i] == 1LL && B[i - 1] == -1LL)) {
			B[i] = 0LL;
			B[i - 1] *= -1LL;
		}
	}
	
	ll lnonzero = N + MG - 1, fnonzero = 0;
	while (lnonzero > 0 && B[lnonzero] == 0LL) --lnonzero;
	while (fnonzero + 1 < N + MG && B[fnonzero] == 0LL) ++fnonzero;
	
//	cerr << lnonzero << ' ' << fnonzero << endl;
	
	vi B2(B.size(), 0LL);
	for (size_t i = 0; i < B.size(); ++i)
		B2[i] = B[i];
	
	ll lsign = B[lnonzero];
	
//	cerr << "This is B: ";
//	for (int i = 0; i <= lnonzero; ++i)
//		cerr << B[i] << " ";
//	cerr << endl << endl;
	
	ll ans = 0LL;
	for (int i = min(N - 1, fnonzero); i >= 0 && i >= fnonzero - 30; --i) {
		
		ll add = K - A[i];
		ll sub = - A[i] - K;
		
		if (lsign < 0) {
			bool ok = true;
			int j = i;
			B2[j] += add;
			ll lastsign = 0LL;
			while (ok && j < N + MG) {
				if (B2[j] == 0LL) break;
				int sign = (B2[j] > 0LL ? 1 : -1);
				B2[j] *= sign;
				B2[j + 1] += sign * (B2[j] / 2LL);
				B2[j] = sign * (B2[j] % 2);
				if (B2[j] != 0)
					lastsign = B2[j];
				++j;
			}
			if (lastsign >= 0LL && j >= lnonzero)
				++ans;
			for (int j2 = i; j2 <= j && j2 < N + MG; ++j2)
				B2[j2] = B[j2];
		} else {
		
			bool ok = true;
			int j = i;
			B2[j] += sub;
			ll lastsign = 0LL;
			while (ok && j < N + MG) {
				if (B2[j] == 0LL) break;
				int sign = (B2[j] > 0LL ? 1 : -1);
				B2[j] *= sign;
				B2[j + 1] += sign * (B2[j] / 2LL);
				B2[j] = sign * (B2[j] % 2);
				if (B2[j] != 0)
					lastsign = B2[j];
				++j;
			}
//			for (int jj = 0; jj < 10; ++jj)
//				cerr << B2[jj] << " ";
//			cerr << endl;
//			cerr << j << endl;
			if (lastsign <= 0LL && j >= lnonzero)
				++ans;
			for (int j2 = i; j2 <= j && j2 < N + 40; ++j2)
				B2[j2] = B[j2];
		}
	}
	
	// correct for a_n = 0
	A[N - 1] = 0LL;
	B.assign(B.size(), 0LL);
	for (int i = 0; i + 1 < B.size(); ++i) {
		if (B[i] == 0LL && i >= N) break;
		if (i < N) B[i] += A[i];
		if (B[i] == 0LL) continue;
		ll sign = (B[i] > 0 ? 1LL : -1LL);
		B[i] *= sign;
		B[i + 1] += sign * (B[i] / 2LL);
		B[i] = sign * (B[i] % 2LL);
	}
	bool zero = true;
	for (int i = 0; i < B.size(); ++i)
		zero = zero && B[i] == 0LL;
	if (zero) -- ans;
	
	cout << ans << endl;
	
	return 0;
}
