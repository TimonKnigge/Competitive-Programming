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

bool isopener(char c) {
	return (c == '(' || c == '<' || c == '{' || c == '[');
}
bool ispair(char c1, char c2) {
	return ((c1 == '(' && c2 == ')')
		|| (c1 == '<' && c2 == '>')
		|| (c1 == '{' && c2 == '}')
		|| (c1 == '[' && c2 == ']'));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	cin >> s;
	stack<char> st;
	int cost = 0;
	for (int i = 0; cost >= 0 && i < int(s.length()); ++i) {
		if (isopener(s[i])) {
			st.push(s[i]);
			continue;
		} else {
			if (st.empty()) cost = -1;
			else {
				if (!ispair(st.top(), s[i]))
					cost++;
				st.pop();
			}
		}
	}
	if (!st.empty()) cost = -1;
	
	if (cost < 0) cout << "Impossible" << endl;
	else cout << cost << endl;
	
	return 0;
}
