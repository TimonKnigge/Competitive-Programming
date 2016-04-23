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

inline int id(char c) {
	if (c == 'A') return 0;
	if (c == 'C') return 1;
	if (c == 'G') return 2;
	return 3;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	vector<string> name, dna;
	string str;
	while (getline(cin, str)) {
		if (str[0] == '>') {
			name.push_back(str);
			dna.push_back("");
		} else	dna.back() += str;
	}
	
	for (size_t i = 0; i < name.size(); ++i)
		name[i].erase(0, 1);
	
	vvi start(64, vi()), end(64, vi());
	for (size_t i = 0; i < dna.size(); ++i) {
		if (dna[i].length() < 3) continue;
		int pref = 0, suff = 0;
		for (size_t j = 0, p = 1; j < 3; ++j, p *= 4)
			pref += id(dna[i][j]) * p,
			suff += id(dna[i][dna[i].length() - 3 + j]) * p;
		start[suff].push_back(i);
		end  [pref].push_back(i);
	}
	
	for (size_t id = 0; id < 64; ++id)
		for (size_t s = 0; s < start[id].size(); ++s)
			for (size_t e = 0; e < end[id].size(); ++e)
				if (start[id][s] != end[id][e])
					cout << name[start[id][s]] << " ",
					cout << name[end  [id][e]] << "\n";
	
	return 0;
}
