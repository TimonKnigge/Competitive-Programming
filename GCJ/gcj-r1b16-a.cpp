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

vector<string> name;
vector<int> order;

void solve(int t) {
	string S;
	cin >> S;
	vi c(26, 0LL);
	for (size_t i = 0; i < S.size(); ++i)
		c[S[i] - 'A']++;
	
	vi ans(10LL, 0);
	for (int j = 0; j < 10; ++j) {
		int i = order[j];
		
		while (true) {
			bool y = true;
			for (size_t k = 0; k < name[i].size(); ++k) {
				c[name[i][k] - 'A']--;
				y = y && c[name[i][k] - 'A'] >= 0;
			}
			if (y) ++ans[i];
			else {
				for (size_t k = 0; k < name[i].size(); ++k) {
					c[name[i][k] - 'A']++;
				}
				break;
			}
		}
	}
	cout << "Case #" << t << ": ";
	for (int i = 0; i < 10; ++i)
		while (ans[i] > 0) cout << i, --ans[i];
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	name.push_back("ZERO");
	name.push_back("ONE");
	name.push_back("TWO");
	name.push_back("THREE");
	name.push_back("FOUR");
	name.push_back("FIVE");
	name.push_back("SIX");
	name.push_back("SEVEN");
	name.push_back("EIGHT");
	name.push_back("NINE");
	
	order.push_back(0);
	order.push_back(8);
	order.push_back(6);
	order.push_back(2);
	order.push_back(3);
	order.push_back(4);
	order.push_back(5);
	order.push_back(7);
	order.push_back(9);
	order.push_back(1);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		solve(t);
	}
	
	return 0;
}
