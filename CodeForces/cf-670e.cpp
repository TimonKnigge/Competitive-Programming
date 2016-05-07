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
	
	int N, P, M;
	string B, O;
	cin >> N >> M >> P >> B >> O;
	
	vi match(N, -1), L(N, -1), R(N, -1);
	stack<ll> st;
	for (int i = 0; i < N; ++i) {
		L[i] = i - 1;
		R[i] = (i + 1 < N ? i + 1 : -1);
		if (B[i] == '(')
			st.push(i);
		else {
			match[i] = st.top();
			match[st.top()] = i;
			st.pop();
		}
	}
	
	--P;
	for (size_t i = 0; i < O.size(); ++i) {
		if (O[i] == 'L') P = L[P];
		if (O[i] == 'R') P = R[P];
		if (O[i] == 'D') {
			int PM = match[P], ml, mr;
			if (B[P] == '(')
				ml = L[P], mr = R[PM];
			else	ml = L[PM], mr = R[P];
			if (ml != -1) R[ml] = mr;
			if (mr != -1) L[mr] = ml;
			P = (mr != -1 ? mr : ml);
		}
	}
	
	while (L[P] != -1) P = L[P];
	while (P != -1) cout << B[P], P = R[P];
	cout << endl;
	
	return 0;
}
