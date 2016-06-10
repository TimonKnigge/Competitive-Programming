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
	
	string s;
	vector<string> ss;
	while (getline(cin, s)) ss.push_back(s);
	while (ss.back().size() == 0) ss.pop_back();
	
	vii sz;
	for (size_t i = 0; i < ss.size(); ++i) sz.push_back({ss[i].size(), i});
	sort(sz.rbegin(), sz.rend());
	
	vi cnt[26];
	for (size_t i = 0; i < 26; ++i) cnt[i].assign(ss.size(), 0);
	vector<vector<char>> owner(ss.size(), vector<char>());
	vi mask(ss.size(), 0LL);
	
	for (size_t i = 0; i < ss.size(); ++i)
		for (char c : ss[i]) {
			if ((cnt[c-'a'][i]++) == 0)
				owner[i].push_back(c);
			mask[i] = mask[i] | (1<<(c-'a'));
		}
	
	vb dom(ss.size(), false);
	for (size_t l = 0, r = 0; l < ss.size(); l = r) {
		while (r < ss.size() && sz[r].first == sz[l].first) ++r;
		for (size_t i = l; i < r; ++i) {
			int id = sz[i].second;
			for (size_t j = 0; !dom[id] && j < l; ++j) {
				if (dom[sz[j].second]) continue;
				if (owner[id].size() > owner[sz[j].second].size())
					continue;
				if ((mask[id]&~mask[sz[j].second]) != 0LL)
					continue;
//				cerr << "checking " << id << " against " << sz[j].second << endl;
				bool d = true;
				for (char c : owner[id])
					d = d && cnt[c-'a'][id] <= cnt[c-'a'][sz[j].second];
				dom[id] = dom[id] || d;
			}
		}
	}
	
	vi ans;
	for (size_t i = 0; i < ss.size(); ++i)
		if (!dom[i]) ans.push_back(i);
	sort(ans.begin(), ans.end(), [&](ll l, ll r) {
		return ss[l] < ss[r];
	});
	
	for (ll i : ans) cout << ss[i] << '\n';
	
	return 0;
}
