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
	vector<string> A(N, "");
	vector<int> v;
	for (int i = 0; i < N; ++i)
		cin >> A[i], v.push_back(i);
	
	sort(v.begin(), v.end(), [&A, &N](int l, int r) {
		int sm = 0, al = A[l].size(), ar = A[r].size();
		for (size_t i = 0; i < al + ar; ++i)
			if (A[i < al ? l : r][i < al ? i : i - al]
			 == A[i < ar ? r : l][i < ar ? i : i - ar]) continue;
			else {
				sm = (A[i < al ? l : r][i < al ? i : i - al]
			 	 < A[i < ar ? r : l][i < ar ? i : i - ar])
					? -1 : 1;
				break;
			}
		return (sm == -1);
	});
	
	for (int i = 0; i < N; ++i)
		cout << A[v[i]];
	cout << endl;
	
	return 0;
}
