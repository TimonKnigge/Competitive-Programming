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
using ii = pair<int,int>;
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
	vi A(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	sort(A.begin(), A.end());
	
	ll denom = N * (N - 1) / 2LL;
	ll denom2 = denom * denom;
	vi diff(5010, 0);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < i; ++j)
			diff[A[i] - A[j]]++;
	vi diff2(10030, 0);
	for (int d = 0; d < 5010; ++d)
		for (int dd = 0; dd < 5010; ++dd)
			diff2[d + dd] += diff[d] * diff[dd];
	
	vi diffpup(5010, 0);
	for (int i = 5008; i >= 0; --i) 
		diffpup[i] = diffpup[i + 1] + diff[i];
	
//	cout << "j\tdiff\tdiff2\tdiffpup" << endl;
//	for (int j = 0; j < 20; ++j)
//		cout << j << '\t' <<  diff[j] << '\t' << diff2[j] << '\t' <<diffpup[j] << endl;
		
	
	ld ans = 0.0;
	for (int d2 = 1; d2 < 5008; ++d2) {
		ans += (ld(diff2[d2]) / ld(denom2)) * (ld(diffpup[d2+1]) / ld(denom));
	}
	
	printf("%.7lf\n", double(ans));
	
	return 0;
}
