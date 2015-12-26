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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const ll LLINF = 9000000000000000000;

int main() {
	
	int n, p, q;
	string str;
	cin >> n >> p >> q >> str;
	vi par(n + 1, -1);
	par[0] = -2;
	for (int i = 0; i + p <= n; ++i)
		if (par[i] != -1)
			par[i + p] = i;
	for (int i = 0; i + q <= n; ++i)
		if (par[i] != -1)
			par[i + q] = i;

	if (par[n] == -1)
		cout << -1 << endl;
	else {
		vi s;
		int i = n;
		while (i > 0) {
			s.push_back(par[i]);
			i = par[i];
		}
		sort(s.begin(), s.end());
		cout << int(s.size()) << endl;
		s.push_back(n);
		for (int i = 0; i + 1 < s.size(); ++i) {
			for (int j = s[i]; j < s[i + 1]; ++j)
				cout << str[j];
			cout << endl;
		}
	}
	
	return 0;
}
