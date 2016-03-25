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
	
	int N;
	scanf("%d", &N);
	vector<int> A(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	
	sort(A.begin(), A.end());
	
	for (int l = 0, r = N - 1; l <= r; ++l, --r) {
		if (l != 0)
			cout << ' ';
		cout << A[l];
		if (l != r)
			cout << ' ' << A[r];
	}
	cout << endl;
	
	return 0;
}
