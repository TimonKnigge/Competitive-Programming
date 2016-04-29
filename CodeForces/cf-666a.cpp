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
	
	string S;
	cin >> S;
	set<string> ans;
	
	vb pos2(S.size() + 1, false);
	vb pos3(S.size() + 1, false);
	pos2[S.size()] = true;
	pos3[S.size()] = true;
	for (int i = int(S.size()) - 1; i >= 5; --i) {
		if (i + 2 <= S.size() && (i + 2 == S.size()
			|| (pos2[i+2] && (S[i] != S[i+2] || S[i+1] != S[i+3]))
			|| pos3[i+2])) {
			pos2[i] = true;
			ans.insert(S.substr(i, 2));
		}
		if (i + 3 <= S.size() && (i + 3 == S.size()
			|| (pos3[i+3] && (S[i]!=S[i+3]||S[i+1]!=S[i+4]||S[i+2]!=S[i+5]))
			|| pos2[i+3])) {
			pos3[i] = true;
			ans.insert(S.substr(i, 3));
		}
	}
	
	cout << ans.size() << endl;
	for (auto &&s : ans)
		cout << s << '\n';
	
	return 0;
}
