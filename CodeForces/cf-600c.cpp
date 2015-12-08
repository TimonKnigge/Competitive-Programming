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
	
	vi c(26, 0);
	string s;
	cin >> s;

	for (int i = 0; i < s.length(); ++i) {
		c[s[i] - 'a']++;
	}
	
	vi odd;
	for (int i = 0; i < 26; ++i)
		if (c[i] % 2 == 1) odd.push_back(i);
	
	for (int j = 0; j < odd.size() / 2; ++j) {
		c[odd[j]]++;
		c[odd[odd.size() - 1 - j]]--;
	}
	
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < c[i] / 2; ++j)
			cout << char('a' + i);
	
	if (s.length() % 2 == 1) 
		cout << char('a' + odd[odd.size()/2]);
	
	for (int i = 25; i >= 0; --i)
		for (int j = 0; j < c[i] / 2; ++j)
			cout << char('a' + i);
	
	cout << endl;
	
	return 0;
}
