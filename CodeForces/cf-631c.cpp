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
	
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<int> A(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	
	vector<ii> flip;
	while (M--) {
		int t, p;
		scanf("%d %d", &t, &p);
		if (flip.size() > 0 && flip.back().first == t)
			flip.back().second = max(flip.back().second, ll(p));
		else	flip.push_back({t, p});
	}
	
	vector<ii> flip2;
	for (int i = int(flip.size()) - 1; i >= 0; --i) {
		if (flip2.size() == 0) flip2.push_back(flip[i]);
		else {
			if (flip2.back().first == flip[i].first)
				flip2.back().second = max(flip2.back().second, flip[i].second);
			else if (flip2.back().second < flip[i].second)
				flip2.push_back(flip[i]);
		}
	}
	
	int L = 0, R = flip2.back().second - 1;
	for (int i = int(flip2.size()) - 1; i > 0; --i) {
		flip2[i].second -= flip2[i-1].second;
	}

	vector<int> B(A);
	sort(A.begin(), A.begin() + R + 1);

	int j = R;
	for (int i = int(flip2.size()) - 1; i >= 0; --i) {
//		cerr << j << ' '<< L << ' ' << R<< endl;
//		for (int z = 0; z < A.size(); ++z)
//			cerr << "  " << A[z];
//		cerr << endl;
		if (flip2[i].first == 1) {
			for (int k = 0; k < flip2[i].second; ++k)
				B[j--] = A[R--];
		} else {
			for (int k = 0; k < flip2[i].second; ++k)
				B[j--] = A[L++];
		}
	}
	
	for (size_t i = 0; i < B.size(); ++i)
		cout << B[i] << " \n"[i + 1 == B.size()];
	
	return 0;
}
