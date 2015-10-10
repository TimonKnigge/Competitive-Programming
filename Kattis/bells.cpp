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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void apply(vi &row, vi &perm) {
	for (int i : perm) {
		swap(row[i], row[i+1]);
	}
}

void precomp(vector<vvi> &v, int N = 8) {
	v.assign(9, vvi());
	v[2].push_back(vi(1, 0));
	v[2].push_back(vi(1, 0));
	v[3].push_back(vi(1, 0));
	v[3].push_back(vi(1, 1));
	v[3].push_back(vi(1, 0));
	v[3].push_back(vi(1, 1));
	v[3].push_back(vi(1, 0));
	v[3].push_back(vi(1, 1));
	
	for (int n = 4; n <= N; ++n) {
		vi perm(n, 0);
		for (int i = 0; i < n; ++i) perm[i] = i;
		
		vb had(n, false);
		had[n - 1] = true;
		for (int i = 0; i < v[n - 1].size(); ++i) {
			// If the next permutation leaves perm[n-1]
			// unchanged and perm[n-1] has not been at the
			// back yet, apply (n-1 n) as well, enumerate
			// all v[n-1] permutations on the current perm
			// and add (n-1 n) to the final permutation
			// as well.
			// Otherwise, just apply
			bool fixed = true;
			for (int _j = 0; _j < v[n - 1][i].size(); ++_j) {
				int j = v[n-1][i][_j];
				fixed = fixed && (n - 3 != j);
			}
			if (fixed && !had[perm[n - 2]]) {
				had[perm[n-2]] = true;
				// Merge (n-1 n), apply v[n-1] fully
				v[n].push_back(v[n-1][i]);
				apply(perm, v[n].back());
				v[n].back().push_back(n - 2);
				for (int j = i + 1; j < v[n-1].size(); ++j)
					v[n].push_back(v[n - 1][j]);
				for (int j = 0; j <= i; ++j)
					v[n].push_back(v[n - 1][j]);
				v[n].back().push_back(n - 2);
			} else {
				// Just apply v[n - 1][i]
				v[n].push_back(v[n-1][i]);
				apply(perm, v[n].back());
			}
		}
	}
}

void printperm(vi &perm) {
	printf("%d", 1 + perm[0]);
	for (int i = 1; i < perm.size(); ++i)
		printf(" %d", 1 + perm[i]);
	printf("\n");
}

int main() {
	vector<vvi> v;
	int n;
	scanf("%d", &n);
	precomp(v, n);
	
	if (n == 1) { printf("1\n"); return 0; }
	
	vi perm(n, 0);
	for (int i = 0; i < n; ++i) perm[i] = i;
	for (int i = 0; i < v[n].size(); ++i) {
//		for (int j : v[n][i]) cerr <<"(" << j << " " << j+1 <<")";
//		cerr<<endl;
		printperm(perm);
		apply(perm, v[n][i]);
	}
//	printf("Size: %d\n", int(v[n].size()));
	
	return 0;
}
