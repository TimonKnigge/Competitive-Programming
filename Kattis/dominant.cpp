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
	
	string s;
	vector<string> ss;
	while (getline(cin, s)) ss.push_back(s);
	while (ss.back().length() == 0) ss.pop_back();
	
	int N = ss.size();
	vvi cnt(26, vi(N, 0));
	vvi cs(N, vi());
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < int(ss[i].size()); ++j) {
			int k = int(ss[i][j] - 'a');
			if (cnt[k][i] == 0) cs[i].push_back(k);
			cnt[k][i]++;
		}
	}
	
	vector<string> dm;
	for (int i = 0; i < N; ++i) {
		bool d = false;
		for (int j = 0; !d && j < N; ++j) {
			if (i == j) continue;
			
			bool dd = cs[i].size() <= cs[j].size();
			dd = dd && ss[i].length() < ss[j].length();
			for (int c = 0; dd && c < int(cs[i].size()); ++c) {
				dd = dd && cnt[cs[i][c]][i] <= cnt[cs[i][c]][j];
			}
			d = d || dd;
		}
		if (!d) dm.push_back(ss[i]);
	}
	
	sort(dm.begin(), dm.end());
	for (int i = 0; i < int(dm.size()); ++i) {
		cout << dm[i] << '\n';
	}
	
	return 0;
}
