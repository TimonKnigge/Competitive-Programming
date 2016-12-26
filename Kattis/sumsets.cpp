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

int overlap(ii l, ii r) {
	return (l.first == r.first) + (l.first == r.second)
		+ (l.second == r.first) + (l.second == r.second);
}

ll solve(vector<pair<ll, ii>> &ab, size_t abl, size_t abr, 
	 vector<pair<ll, ii>> &cd, size_t cdl, size_t cdr, vi &A, ll best) {
	// For all i,j \in ab i > j
	// For all i,j \in neg < pos
	
	vii abij(6, ab[abl].second);
	for (size_t i = abl + 1; i < abr; ++i) {
		ii ij = ab[i].second;
		if (abij[1] == abij[0] && ij.first != abij[0].first && ij.second == abij[0].second) abij[1] = ij;
		if (abij[1] == abij[0] && ij.first == abij[0].second && ij.second != abij[0].first) abij[1] = {ij.second, ij.first};
		
		if (abij[4] == abij[0] && ij.first != abij[0].first && ij.second == abij[0].second && ij.first != abij[1].first) abij[4] = ij;
		if (abij[4] == abij[0] && ij.first == abij[0].second && ij.second != abij[0].first && ij.second != abij[1].first) abij[4] = {ij.second, ij.first};
		
		if (abij[2] == abij[0] && ij.first == abij[0].first && ij.second != abij[0].second) abij[2] = ij;
		if (abij[2] == abij[0] && ij.first != abij[0].second && ij.second == abij[0].first) abij[2] = {ij.second, ij.first};
		
		if (abij[5] == abij[0] && ij.first == abij[0].first && ij.second != abij[0].second && ij.second != abij[2].second) abij[5] = ij;
		if (abij[5] == abij[0] && ij.first != abij[0].second && ij.second == abij[0].first && ij.first != abij[2].second) abij[5] = {ij.second, ij.first};
		
		if (abij[3] == abij[0] && overlap(abij[0], ij) == 0) {
			abij[3] = ij;
			break;
		}
	}
	
	for (size_t i = cdl; i < cdr; ++i) {
		ii ij = cd[i].second;
		if (A[ij.second] <= best) continue;
		for (ii &v : abij)
			if (overlap(v, ij) == 0)
				best = A[ij.second];
	}
	return best;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	vi A(N, 0LL);
	ll nc = 0LL;
	for (ll &v : A) {
		cin >> v;
		if (v == 0LL) ++nc;
	}
	sort(A.begin(), A.end());
	
	{
		vi nA;
		for (size_t i = 0; i < A.size(); ++i) {
			if (nA.size() < 3 || any_of(nA.end() - 3, nA.end(),
				[&A, i](const ll &v) { return v != A[i]; }))
				nA.push_back(A[i]);
		}
		swap(A, nA);
	}
	
	// a + b = c - d
	
	vector<pair<ll, ii>> ab, cd;
	for (size_t i = 0; i < A.size(); ++i)
		for (size_t j = i + 1; j < A.size(); ++j)
			ab.push_back({A[i] + A[j], {j, i}}),
			cd.push_back({-A[j]+ A[i], {j, i}}),
			cd.push_back({-A[i]+ A[j], {i, j}});
	sort(ab.rbegin(), ab.rend());
	sort(cd.rbegin(), cd.rend());
	
	ll best = -LLINF;
	if (nc >= 4) best = 0LL;
	size_t abl = 0, cdl = 0;
	while (true) {
		while (abl < ab.size() && cdl < cd.size()
			&& ab[abl].first != cd[cdl].first) {
			while (abl < ab.size() && ab[abl].first > cd[cdl].first) ++abl;
			if (abl == ab.size()) break;
			while (cdl < cd.size() && ab[abl].first < cd[cdl].first) ++cdl;
			if (cdl == cd.size()) break;
		}
		if (abl < ab.size() && cdl < cd.size()) {
			size_t abr = abl, cdr = cdl;
			while (abr < ab.size() && ab[abl].first == ab[abr].first) ++abr;
			while (cdr < cd.size() && cd[cdl].first == cd[cdr].first) ++cdr;
			best = solve(ab, abl, abr, cd, cdl, cdr, A, best);
			abl = abr;
			cdl = cdr;
		} else break;
	}
	
	if (best > -LLINF)
		cout << best << endl;
	else	cout << "no solution" << endl;
	
	return 0;
}
