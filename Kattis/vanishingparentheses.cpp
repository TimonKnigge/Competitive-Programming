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

bool isop(char c) { return c == '+' || c == '-' || c == '*'; }
ll oper(ll l, ll r, char op) {
	if (op == '+') return l+r;
	if (op == '-') return l-r;
	return l*r;
}

void solve(string &S, bool &any) {
	S = S + ' ';
	
	vi values;
	vector<char> operators;
	
	for (size_t i = 0; i < S.size();) {
		size_t j = i;
		while (j < S.size() && S[j] != ' ') ++j;
		
		if (i+1 == j && isop(S[i])) {
			operators.push_back(S[i]);
		} else {
			ll m = 1LL;
			if (S[i] == '-') { m = -1LL; ++i; }
			ll v = 0LL;
			for (size_t k = i; k < j; ++k) v = 10LL*v + (S[k]-'0');
			v *= m;
			values.push_back(v);
		}
		i = j + 1;
	}
	
//	for (ll v : values) cerr << ' ' <<v;cerr << endl;
//	for (char c : operators) cerr << ' ' <<c;cerr << endl;
	
	int V = values.size();
	vector<vector<set<ll>>> pos(V, vector<set<ll>>(V, set<ll>()));
	for (int l = V - 1; l >= 0; --l) {
		pos[l][l].insert(values[l]);
		for (int r = l + 1; r < V; ++r) {
			for (int o = l; o < r; ++o) {
				for (ll lv : pos[l][o])
					for (ll rv : pos[o+1][r])
						pos[l][r].insert(oper(lv, rv, operators[o]));
			}
		}
	}
	
	if (any) cout << '\n';
	else any = true;
	for (ll v : pos[0][V-1]) cout << v << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string S;
	bool any = false;
	while (getline(cin, S)) solve(S, any);
	
	return 0;
}
