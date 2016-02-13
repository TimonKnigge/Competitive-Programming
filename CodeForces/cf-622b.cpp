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

void pn(ll v) {
	if (v < 10) cout << "0";
	cout << v;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll H, M;
	cin >> H;
	char temp;
	cin >> temp;
	cin >> M;
	
	ll A;
	cin >> A;
	M += A;
	H += M / 60;
	M %= 60;
	H %= 24;
	
	pn(H);
	cout << ":";
	pn(M);
	cout << endl;
	
	return 0;
}
