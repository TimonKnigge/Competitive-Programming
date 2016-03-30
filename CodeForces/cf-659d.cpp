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

int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

int main() {
	
	int N;
	scanf("%d", &N);
	
	vector<int> X(N + 1, 0), Y(N + 1, 0);
	for (int i = 0; i < N + 1; ++i)
		scanf("%d %d", &X[i], &Y[i]);
	
	vi dir(N, -1);
	for (int i = 0; i < N; ++i) {
		
		if (X[i] == X[i + 1])
			dir[i] = (Y[i] < Y[i + 1] ? UP : DOWN);
		else	dir[i] = (X[i] < X[i + 1] ? RIGHT : LEFT);
	}
	dir.push_back(dir[0]);
	
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		
		if ((4 + dir[i] - dir[i + 1]) % 4 == 1)
			++ans;
	}
	
	cout << ans << endl;
	
	return 0;
}
