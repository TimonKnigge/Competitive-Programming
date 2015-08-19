#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll N, T, A, B, C, t0;
	cin >> N >> T >> A >> B >> C >> t0;
	
	vector<ll> lp(C + 1, -1);
	lp[t0] = 0;
	ll ts = t0;
	ll lstart = 0, i;
	for (i = 1;;++i) {
		ts = (A * ts + B) % C + 1;
		if (lp[ts] == -1) lp[ts] = i;
		else {
			// Loop!
			lstart = ts;
			break;
		}
	}
	ll looplength = i - lp[lstart];
	
	vector<ll> countof(C + 1, 0);
	ll lef = N;
	for (ts = t0; ts != lstart && lef > 0; ts = (A * ts + B) % C + 1) {
		countof[ts]++;
		lef--;
	}
	// Loop starts at lstart
	for (i = 0, ts = lstart; i < looplength; ++i, ts = (A * ts + B) % C + 1) {
		countof[ts] += lef / looplength;
		if (i < lef % looplength) countof[ts]++;
	}

	ll pr = 0, tm = 0, Tleft = T, Tused = 0, MOD = 1e9+7;
	for (int j = 1; j <= C; ++j) {
		if (countof[j] == 0) continue;
		if (Tleft < j) break;
		ll s = min(countof[j], Tleft / j);
		pr += s;
		Tleft -= j * s;
		ll sM = s % MOD;
		tm = (tm + ((sM * (Tused % MOD)) % MOD)) % MOD;
		if (sM % 2 == 0)
			tm = (tm + ((((sM / 2 * (sM + 1)) % MOD) * j) % MOD)) % MOD;
		else
			tm = (tm + (((((sM + 1) / 2 * sM) % MOD) * j) % MOD)) % MOD;
		Tused += j * s;
	}

	cout << pr << ' ' << (tm % MOD) << endl;
	
	return 0;
}

