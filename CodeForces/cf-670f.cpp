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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S, P;
	cin >> S >> P;
	int sp[10], sc[10];
	for (int d = 0; d < 10; ++d) sp[d] = sc[d] = 0;
	
	for (size_t i = 0; i < S.length(); ++i) ++sc[S[i] - '0'];
	for (size_t i = 0; i < P.length(); ++i) ++sp[P[i] - '0'];
			
	if (S.length() == 2 && sc[0] == sc[1] && sc[0] == 1) {
		cout << 0 << endl;
		return 0;
	}

	int sn[10], N;
	for (size_t D = 7; D >= 1; --D) {
		if (D >= S.length()) continue;
		N = S.length() - D;
		
		// N should have D digits
		// N + P <= S
		for (int i = 0; i < 10; ++i) sn[i] = 0;
		int NN = N, digits = 0;
		while (NN > 0) {
			++sn[NN % 10];
			NN /= 10;
			++digits;
		}
		if (D != digits) continue;
		if (P.length() > N) continue;
		bool y = true, any = P[0] != '0';
		for (int i = 0; i < 10; ++i)
			y = y && sn[i] + sp[i] <= sc[i],
			any = any || (i > 0 && sn[i] + sp[i] < sc[i]);
		if (y && any) break;
	}

	for (int i = 0; i < 10; ++i)
		sc[i] -= sn[i],
		sc[i] -= sp[i];
	
	string ft = P, nft = "";
	for (int d = 0; d < 10; ++d)
		if (sc[d] > 0)
			ft = ft + string(sc[d], char('0' + d));
	
	int pd = P[0] - '0', pd2 = -1;
	for (size_t i = 1; i < P.size(); ++i)
		if (P[i] != P[0]) {
			pd2 = P[i] - '0';
			break;
		}
	
	int d = 1;
	while (sc[d] == 0) ++d;
	nft = string(1, char('0' + d));
	--sc[d];
	
	for (d = 0; d < 10; ++d) {
		if (d == pd && pd2 < pd) {
			nft = nft + P;
		}
		if (sc[d] > 0)
			nft = nft + string(sc[d], char('0' + d));
		if (d == pd && pd2 >= pd) {
			nft = nft + P;
		}
	}
	
	string &ans = ft;
	if (ft[0] == '0' || nft < ft) ans = nft;
	cout << ans << endl;
	
	return 0;
}
