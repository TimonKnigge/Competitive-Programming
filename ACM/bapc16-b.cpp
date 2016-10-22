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
	
	string s;
	cin >> s;
	
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == 'R') s[i] = 'S';
		if (s[i] == 'B') s[i] = 'K';
		if (s[i] == 'L') s[i] = 'H';
	}
	
	const int sum = int('S') + int('K') + int('H');
	for (size_t i = 0; i + 2 < s.size(); ++i) {
		if (int(s[i]) + int(s[i+1]) + int(s[i+2]) == sum) {
			s[i] = 'C';
			s[i+1] = s[i+2] = 'c';
			i += 2;
		}
	}
	
	for (size_t i = 0; i < s.size(); ++i)
		if (s[i] != 'c') cout << s[i];
	cout << endl;
	
	return 0;
}
