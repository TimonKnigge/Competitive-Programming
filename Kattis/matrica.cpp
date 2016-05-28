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
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	vector<pair<char, int>> av(K, {'+', -1});
	for (int k = 0; k < K; ++k)
		scanf(" %c %d", &av[k].first, &av[k].second);
	sort(av.begin(), av.end());
	
	int odds = 0;
	for (int k = 0; k < K; ++k)
		if (av[k].second&1) ++odds;
	
	if (odds > N) {
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}

	int freediag = N-odds;
	vector<char> diag;
	vector<pair<char, int>> triag;
	int row = 0, left = N-1;
	for (int k = 0; k < K; ++k) {
		char c = av[k].first;
		int cnt = av[k].second;
		
		if (cnt&1) {
			cnt--;
			diag.push_back(c);
		}
		
		int intriag = 0;

		while (cnt > 1 && row < N) {
			// Did we pick the current diagonal element already?
			while (diag.size() <= row && freediag>0) {
				--cnt;
				diag.push_back(c);
				--freediag;
			}
//			cerr << c << ' ' << cnt << ' ' << left << ' ' << intriag << endl;
			if (cnt/2 >= left) {
				cnt -= left*2;
				intriag += left;
				row++;
				left = N-row-1;
			} else {
				intriag += cnt/2;
				left -= cnt/2;
				cnt -= 2*(cnt/2);
			}
		}
		while (cnt > 0 && freediag>0) {
			diag.push_back(c);
			--cnt;
			--freediag;
		}
//		cerr << c << " to " << cnt << endl;
		if (intriag > 0) triag.push_back({c, intriag});
	}
	
	int P;
	scanf("%d", &P);
	vector<int> cols(P, 0);
	for (int p = 0; p < P; ++p)
		scanf("%d", &cols[p]),
		--cols[p];
	
	// prefixify triag
	for (size_t i = 1; i < triag.size(); ++i)
		triag[i].second += triag[i-1].second;

//	cout << "diagonal: ";
//	for (char c : diag) cout << c;
//	cout << endl;
//	cout << "triag:";
//	for (pair<char, int> ci : triag) cout << "  " << ci.first << ',' << ci.second;
//	cout << endl;
	
	
	vector<vector<char>> ans(P, vector<char>(N, '-'));
	for (int p = 0; p < P; ++p) {
		int c = cols[p];
		ans[p][c] = diag[c];
		
		// Entries [0..c) are computed in column fashion
		int elem = 0;
		for (int i = 0; i < c; ++i) {
			// Entry (i, c)
			int pos = elem + c-i-1;
			size_t l = 0, r = triag.size();
			while (l < r) {
				size_t m = (l+r)/2;
				if (triag[m].second > pos)
					r = m;
				else	l = m + 1;
			}
			ans[p][i] = triag[l].first;
			elem += N-i-1;
		}
		
		// Entries [c+1, N) are computed in row fashion
		elem = 0;
		for (int i = 0; i < c; ++i) elem += N-1-i;
		for (int i = c+1; i < N; ++i) {
			size_t l = 0, r = triag.size();
			while (l < r) {
				size_t m = (l+r)/2;
				if (triag[m].second > elem)
					r = m;
				else	l = m + 1;
			}
			ans[p][i] = triag[l].first;
			++elem;
		}
	}
	
	
	
	for (int r = 0; r < N; ++r) {
		for (int p = 0; p < P; ++p) {
			cout << ans[p][r];
		}
		cout << endl;
	}
	
	
	return 0;
}
