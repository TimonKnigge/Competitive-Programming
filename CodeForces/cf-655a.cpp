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
	
	string l[4];
	for (int i = 0; i < 4; ++i) {
		cin >> l[i];
//		cerr << ' ' << l[i] << endl;
	}
	
	swap(l[1][0], l[1][1]);
	swap(l[3][0], l[3][1]);
	
	string r[2];
	r[0] = l[0] + l[1];
	r[1] = l[2] + l[3];
//	cerr << r[0] << ' ' << r[1] << endl;
	
	int id[2] = {0, 0};
	for (int i = 0; i < 2; ++i)
		while (r[i][id[i]] != 'A') ++id[i];
	
	string f[2];
	f[0] = f[1] = "";
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j)
			if (r[i][(id[i] + j) % 4] != 'X')
				f[i] = f[i] + r[i][(id[i]+j)%4];
	}
	
	cout << (f[0] == f[1] ? "YES" : "NO") << endl;
	
	return 0;
}
