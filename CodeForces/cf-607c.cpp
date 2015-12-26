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

void Z_algorithm(string &s, vector<int> &Z) {
	Z.assign(s.length(), -1);
	int L = 0, R = 0, n = s.length();
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else if (Z[i - L] >= R - i + 1) {
			L = i;
			while (R < n && s[R - L] == s[R]) R++;
			Z[i] = R - L; R--;
		} else Z[i] = Z[i - L];
	}
	Z[0] = n;
}

char single_invert(char c) {
	if (c == 'W')	return 'E';
	if (c == 'E')	return 'W';
	if (c == 'N')	return 'S';
			return 'N';
}

void invert(string &s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = single_invert(s[i]);
	}
	for (size_t i = 0; i < s.length() / 2; ++i) {
		swap(s[i], s[s.length() - 1 - i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	string s1, s2;
	cin >> n >> s1 >> s2;
	
	invert(s1);
	vi Z;
	string full = s1 + '$' + s2;
	Z_algorithm(full, Z);
	
//	cerr << full << endl;
	
	bool possible = true;
	for (int i = int(s1.length()) + 1; i < int(full.length()); ++i) {
		if (i + Z[i] >= int(full.length()))
			possible = false;
	}
	
	cout << (possible ? "YES" : "NO") << endl;
	
	return 0;
}
