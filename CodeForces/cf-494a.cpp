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

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	string s;
	cin >> s;
	int n = int(s.length());
	
	int open = 0;
	int open_since_last_pound = 0;
	int pounds = 0;
	bool possible = true;
	for (int i = 0; i < n && possible; ++i) {
		if (s[i] == '(') {
			open++;
			open_since_last_pound++;
		} else if (s[i] == ')') {
			if (open > 0) {
				open--;
				if (open_since_last_pound > 0)
					open_since_last_pound--;
			}
			else possible = false;
		} else {
			pounds++;
			open_since_last_pound = 0;
			if (open > 0) open--;
			else possible = false;
		}
	}
	
	possible = possible && (open_since_last_pound == 0);
	
	if (!possible) cout << -1 << endl;
	else {
		for (int i = 0; i < pounds - 1; ++i) cout << 1 << '\n';
		cout << 1 + open << endl;
	}
	
	return 0;
}
