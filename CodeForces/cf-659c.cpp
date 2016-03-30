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
	ll M;
	cin >> N >> M;
	
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	
	sort(A.begin(), A.end());
	
	ll free = 1LL;
	size_t i = 0;
	
	vi res;
	while (free <= M) {
		if (i < A.size() && A[i] == free) ++i;
		else {
			M -= free;
			res.push_back(free);
		}
		++free;
	}
	
	cout << res.size() << endl;
	for (size_t i = 0; i < res.size(); ++i)
		cout << res[i] << " \n"[i + 1 == res.size()];
	
	return 0;
}
