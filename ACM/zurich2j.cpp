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
	
	size_t n;
	cin >> n;
	
	vector<string> sol[13];
	sol[0].push_back("");
	sol[1].push_back("0");
	sol[1].push_back("1");
	sol[2].push_back("00");
	sol[2].push_back("01");
	sol[2].push_back("10");
	sol[2].push_back("11");
	
	for (int i = 3; i <= n; ++i) {
		if (i&1) {
			for (size_t j = 0; j < sol[i-1].size() * 2; ++j)
				sol[i].push_back(sol[i-1][j % sol[i - 1].size()]
					+ (j < sol[i-1].size() ? "0" : "1"));
		} else {
			for (size_t j = 0; j < sol[i-2].size(); j += 2) {
				sol[i].push_back(sol[i-2][ j ] + "00");
				sol[i].push_back(sol[i-2][j+1] + "10");
				sol[i].push_back(sol[i-2][ j ] + "11");
				sol[i].push_back(sol[i-2][j+1] + "01");
				sol[i].push_back(sol[i-2][ j ] + "10");
				sol[i].push_back(sol[i-2][j+1] + "00");
				sol[i].push_back(sol[i-2][ j ] + "01");
				sol[i].push_back(sol[i-2][j+1] + "11");
			}
		}
	}
	
	for (size_t i = 0; i < sol[n].size(); ++i)
		cout << sol[n][i] << '\n';
	
	return 0;
}
