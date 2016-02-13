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

int main() {
	
	int N;
	cin >> N;
	vi out(2 * N, -1);
	
	int l = 0, r = N - 1;
	for (int i = 1; i < N; i += 2) {
		out[l] = i;
		out[r] = i;
		l++; --r;
	}
	int ls = N;
	if (l == r) ls = l;
	l = N;
	r = 2 * N - 2;
	for (int i = 2; i < N; i += 2) {
		out[l] = i;
		out[r] = i;
		l++; --r;
	}
	
	if (l == r) {
		ls = l;
	}
	out[ls] = N;
	out[2*N-1] = N;
	
	for (size_t i = 0; i < out.size(); ++i)
		cout << out[i] << " \n"[i + 1 == out.size()];
	
	
	return 0;
}
