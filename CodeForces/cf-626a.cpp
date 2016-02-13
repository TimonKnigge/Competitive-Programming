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
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int h(char c) {
	if (c == 'L') return -1;
	if (c == 'R') return 1;
	return 0;
}
int v(char c) {
	if (c == 'U') return 1;
	if (c == 'D') return -1;
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	string S;
	cin >> N >> S;
	
	int ans = 0;
	for (int l = 0; l < N; ++l) {
		int H = 0, V = 0;
		for (int r = l; r < N; ++r) {
			H += h(S[r]);
			V += v(S[r]);
			if (H == 0 && V == 0) ans++;
		}
	}
	cout << ans << endl;
	
	return 0;
}
