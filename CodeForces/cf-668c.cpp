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
	
	int N;
	cin >> N;
	vector<ld> M(N, 0.0), m(N, 0.0);
	for (int i = 0; i < N; ++i) cin >> M[i];
	for (int i = 0; i < N; ++i) cin >> m[i];
	
	if (N == 1) {
		cout << "1.0\n1.0\n";
		return 0;
	}
	
	vector<ld> mpref(m), msuff(m);
	vector<ld> Mpref(M), Msuff(M);
	for (int i = 1; i < N; ++i)
		mpref[i] += mpref[i - 1],
		Mpref[i] += Mpref[i - 1];
	for (int i = N - 2; i >= 0; --i)
		msuff[i] += msuff[i + 1],
		Msuff[i] += Msuff[i + 1];
	
	ld s = 1.0 - msuff[1] + M[0];
	ld p = M[0];
	
	:wq

	
	
	return 0;
}
