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
	
	int n;
	cin >> n;
	vvi sc(26, vi(26, 0));
	while (n--) {
		vi c(26, 0);
		string s;
		cin >> s;
		for (int i = 0; i < s.size(); ++i) {
			c[s[i] - 'a']++;
		}
		
		vi pos;
		for (int i = 0; i < 26; ++i)
			if (c[i] > 0) pos.push_back(i);
		
		if (pos.size() == 2) {
			sc[pos[0]][pos[1]] += s.size(); 
			sc[pos[1]][pos[0]]+=s.size();
		}
		if (pos.size() == 1) {
			for (int j = 0; j < 26; ++j) {
				if (j == pos[0]) continue;
				sc[pos[0]][j] += s.size();
				sc[j][pos[0]] += s.size();
			}
			
		}
	}
	
	int M = 0;
	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j)
			if (sc[i][j] > M) M = sc[i][j];
	cout << M << endl;
	
	return 0;
}
