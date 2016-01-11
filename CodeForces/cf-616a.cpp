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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s1, s2;
	cin >> s1 >> s2;
	
	int start1 = 0, start2 = 0;
	while (start1 < s1.length() && s1[start1] == '0') ++start1;
	while (start2 < s2.length() && s2[start2] == '0') ++start2;
	
	if (s1.length() - start1 < s2.length() - start2) {
		cout << '<' << endl;
		 return 0;
	}
	else if (s1.length() - start1> s2.length() - start2) {
		cout << '>' << endl;
		return 0;
	}
	else {
		for (size_t i = 0; i < s1.length() - start1; ++i) {
			if (s1[start1+i] == s2[start2+i]) continue;
			if (s1[start1+i] < s2[start2+i]) cout << '<' << endl;
			else cout << '>' << endl;
			return 0;
		}
	}
	
	cout << '=' << endl;
	return 0;
}
