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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string pas, str;
	cin >> pas >> str;
	
	vi c(26, 0);
	for (size_t i = 0; i < pas.length(); ++i)
		c[pas[i] - 'A']++;
	
	size_t i = 0;
	bool fail = false;
	for (size_t j = 0; !fail && j < str.length(); ++j) {
		if (c[str[j] - 'A'] == 0) continue;
		if (pas[i] == str[j]) {
			c[pas[i] - 'A']--;
			i++;
		} else fail = true;
	}
	
	fail = fail || (i != pas.length());
	cout << (fail ? "FAIL\n" : "PASS\n");
	
	return 0;
}
